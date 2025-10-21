#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <fcntl.h>
#include <algorithm>
#include <csignal>

struct Command {
    std::string cmd;
    std::string next_op;
    std::string out_file;
    bool append = false;
    bool background = false;
    bool silent = false;
};

void trim(std::string &s) {
    s.erase(0, s.find_first_not_of(" \t"));
    s.erase(s.find_last_not_of(" \t") + 1);
}

std::vector<Command> parse_line(const std::string &line) {
    std::vector<Command> cmds;
    size_t pos = 0, last = 0;

    while (pos < line.size()) {
        std::string op;
        if (line.compare(pos, 2, "&&") == 0) op = "&&";
        else if (line.compare(pos, 2, "||") == 0) op = "||";
        else if (line[pos] == ';') op = ";";

        if (!op.empty()) {
            std::string part = line.substr(last, pos - last);
            trim(part);
            if (!part.empty()) {
                Command c;
                c.cmd = part;
                c.next_op = op;

                if (c.cmd.find("silent ") == 0) {
                    c.silent = true;
                    c.cmd = c.cmd.substr(7);
                    trim(c.cmd);
                }

                if (!c.cmd.empty() && c.cmd.back() == '&') {
                    c.background = true;
                    c.cmd.pop_back();
                    trim(c.cmd);
                }

                size_t red_pos = c.cmd.find(">>");
                if (red_pos != std::string::npos) {
                    c.out_file = c.cmd.substr(red_pos + 2);
                    trim(c.out_file);
                    c.cmd = c.cmd.substr(0, red_pos);
                    trim(c.cmd);
                    c.append = true;
                } else {
                    red_pos = c.cmd.find('>');
                    if (red_pos != std::string::npos) {
                        c.out_file = c.cmd.substr(red_pos + 1);
                        trim(c.out_file);
                        c.cmd = c.cmd.substr(0, red_pos);
                        trim(c.cmd);
                    }
                }

                cmds.push_back(c);
            }

            pos += op.size();
            last = pos;
        } else pos++;
    }

    std::string part = line.substr(last);
    trim(part);
    if (!part.empty()) {
        Command c;
        c.cmd = part;

        if (c.cmd.find("silent ") == 0) {
            c.silent = true;
            c.cmd = c.cmd.substr(7);
            trim(c.cmd);
        }

        if (!c.cmd.empty() && c.cmd.back() == '&') {
            c.background = true;
            c.cmd.pop_back();
            trim(c.cmd);
        }

        size_t red_pos = c.cmd.find(">>");
        if (red_pos != std::string::npos) {
            c.out_file = c.cmd.substr(red_pos + 2);
            trim(c.out_file);
            c.cmd = c.cmd.substr(0, red_pos);
            trim(c.cmd);
            c.append = true;
        } else {
            red_pos = c.cmd.find('>');
            if (red_pos != std::string::npos) {
                c.out_file = c.cmd.substr(red_pos + 1);
                trim(c.out_file);
                c.cmd = c.cmd.substr(0, red_pos);
                trim(c.cmd);
            }
        }

        cmds.push_back(c);
    }

    return cmds;
}

int do_command(const Command &c) {
    std::istringstream iss(c.cmd);
    std::vector<std::string> args;
    std::string token;
    while (iss >> token) args.push_back(token);
    if (args.empty()) return 1;

    if (args[0] == "cd") {
        const char* dir = args.size() > 1 ? args[1].c_str() : getenv("HOME");
        if (chdir(dir) != 0) perror("cd");
        return 0;
    }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        if (c.silent) {
            std::string log = std::to_string(getpid()) + ".log";
            int fd = open(log.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd >= 0) { dup2(fd, STDOUT_FILENO); dup2(fd, STDERR_FILENO); close(fd); }
        }

        if (!c.out_file.empty()) {
            int fd = open(c.out_file.c_str(),
                          c.append ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC),
                          0644);
            if (fd < 0) { perror("open"); _exit(1); }
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);
        }

        std::vector<char*> cargs;
        for (auto &a : args) cargs.push_back(&a[0]);
        cargs.push_back(nullptr);

        execvp(cargs[0], cargs.data());
        perror("execvp");
        _exit(1);

    } else {
        if (!c.background) {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) return WEXITSTATUS(status);
            else return 1;
        } else {
            std::cout << "[bg] pid " << pid << "\n";
        }
    }

    return 0;
}

int main() {
    signal(SIGINT, SIG_IGN);
    const char* user = getenv("USER");
    std::string line;

    while (true) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd))) {
            std::string path(cwd);
            const char* home = getenv("HOME");
            if (home && path.find(home) == 0) path.replace(0, std::string(home).size(), "~");
            std::cout << (user ? user : "user") << "@shell:" << path << "$ " << std::flush;
        } else {
            std::cout << (user ? user : "user") << "@shell:? $ " << std::flush;
        }

        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        if (line == "exit") break;

        auto commands = parse_line(line);
        int last_status = 0;

        for (size_t i = 0; i < commands.size(); i++) {
            Command &c = commands[i];

            if ((i > 0 && commands[i-1].next_op == "&&" && last_status != 0) ||
                (i > 0 && commands[i-1].next_op == "||" && last_status == 0)) {
                continue;
            }

            last_status = do_command(c);
        }
    }
}
