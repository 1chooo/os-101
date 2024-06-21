pseudo code in shell

```c
#define TRUE 1

while (TRUE) {                        // Repeat indefinitely
    type_prompt();                  // Display prompt on screen
    read_command(command, parameters);  // read input from process

    if (fork() != 0) {                  // fork off child process
        // Parent
        waitpid(-1, &status, 0);        // Wait for child to exit
    } else {
        // Child
        execve(command, parameters, 0); // Execute command
    }
}
```

shell
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TRUE 1
#define MAX_LINE 1024
#define MAX_ARGS 64

void type_prompt() {
    printf("> ");
}

void read_command(char *command, char **parameters) {
    char line[MAX_LINE];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        perror("fgets failed");
        exit(1);
    }

    // Remove the newline character if present
    line[strcspn(line, "\n")] = '\0';

    // Tokenize the input line into command and parameters
    char *token = strtok(line, " ");
    if (token == NULL) {
        command[0] = '\0';  // Empty command
        return;
    }
    strcpy(command, token);

    int i = 0;
    while (token != NULL && i < MAX_ARGS - 1) {
        parameters[i++] = token;
        token = strtok(NULL, " ");
    }
    parameters[i] = NULL;  // Null-terminate the parameters array
}

int main() {
    char command[MAX_LINE];
    char *parameters[MAX_ARGS];
    int status;

    while (TRUE) {  // Repeat indefinitely
        type_prompt();  // Display prompt on screen
        read_command(command, parameters);  // Read input from user

        if (strlen(command) == 0) {
            continue;  // Skip empty commands
        }

        if (fork() != 0) {  // Fork off child process
            // Parent process
            waitpid(-1, &status, 0);  // Wait for child to exit
        } else {
            // Child process
            execve(command, parameters, NULL);  // Execute command
            // If execve returns, it must have failed
            perror("execve failed");
            exit(1);  // Exit child process with error code
        }
    }

    return 0;
}
```

shell
```go
package main

import (
    "bufio"
    "fmt"
    "os"
    "os/exec"
    "strings"
    "syscall"
)

func typePrompt() {
    fmt.Print("> ")
}

func readCommand() (string, []string) {
    reader := bufio.NewReader(os.Stdin)
    commandLine, _ := reader.ReadString('\n')
    commandLine = strings.TrimSpace(commandLine)
    parts := strings.Fields(commandLine)
    if len(parts) == 0 {
        return "", nil
    }
    command := parts[0]
    parameters := parts[1:]
    return command, parameters
}

// func main() {
//     for {
//         typePrompt()
//         command, parameters := readCommand()
//         if command == "" {
//             continue
//         }

//         cmd := exec.Command(command, parameters...)
//         cmd.SysProcAttr = &syscall.SysProcAttr{Setpgid: true}

//         cmd.Stdout = os.Stdout
//         cmd.Stderr = os.Stderr
//         cmd.Stdin = os.Stdin

//         if err := cmd.Start(); err != nil {
//             fmt.Println("Error:", err)
//             continue
//         }

//         if err := cmd.Wait(); err != nil {
//             fmt.Println("Error:", err)
//         }
//     }
// }
```


fork
```go
package main

import (
	"flag"
	"fmt"
	"os"
	"os/exec"
	"strconv"
	"sync"
)

func calculateSumWithFormula(len int) int {
	return len * (len + 1) / 2
}

func calculateSumWithLoop(len int) int {
	sum := 0
	for i := 0; i <= len; i++ {
		sum += i
	}
	return sum
}

func forkImplement(mode int) {
	len := 35000
	var sum int

	if mode == 1 {
		var wg sync.WaitGroup
		wg.Add(1)
		go func() {
			defer wg.Done()
			sum = calculateSumWithLoop(len)
			fmt.Printf("sum : %d. ", sum)
			fmt.Printf("Parent process! pid : %d.\n", os.Getpid())
		}()
		wg.Wait()

		childProcess(len)
	} else if mode == 2 {
		childProcess(len)

		sum = calculateSumWithLoop(len)
		fmt.Printf("sum : %d. ", sum)
		fmt.Printf("Parent process! pid : %d.\n", os.Getpid())
	} else {
		go childProcess(len)

		sum = calculateSumWithLoop(len)
		fmt.Printf("sum : %d. ", sum)
		fmt.Printf("Parent process! pid : %d.\n", os.Getpid())
	}
}

func childProcess(len int) {
	cmd := exec.Command(os.Args[0], "child", strconv.Itoa(len))
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	if err := cmd.Run(); err != nil {
		fmt.Printf("Error running child process: %v\n", err)
	}
}

func child(len int) {
	sum := calculateSumWithFormula(len)
	fmt.Printf("sum : %d. ", sum)
	fmt.Printf("Child process! pid : %d.\n", os.Getpid())
}

func printHelp() {
	fmt.Println("-h : Print this help.")
	fmt.Println("-d : Implement fork in default mode.")
	fmt.Println("-c : Implement fork in child first mode.")
	fmt.Println("-p : Implement fork in parent first mode.")
}

func main() {
	help := flag.Bool("h", false, "Print help message")
	defaultMode := flag.Bool("d", false, "Implement fork in default mode")
	childFirst := flag.Bool("c", false, "Implement fork in child first mode")
	parentFirst := flag.Bool("p", false, "Implement fork in parent first mode")
	flag.Parse()

	if *help {
		printHelp()
		return
	}

	if len(os.Args) > 1 && os.Args[1] == "child" {
		len, _ := strconv.Atoi(os.Args[2])
		child(len)
		return
	}

	if *defaultMode {
		forkImplement(0)
	} else if *childFirst {
		forkImplement(1)
	} else if *parentFirst {
		forkImplement(2)
	} else {
		fmt.Println("Incorrect command option.")
		printHelp()
	}
}
```