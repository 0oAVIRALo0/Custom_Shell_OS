# Custom_Shell_OS

SHELL:
  INTERNAL COMMANDS:
    Cd - changes the current working directory
      L:  symbolic components are handled in the directory before dot-dot (“..”) components. 
      P:  symbolic components are handled in the directory after dot-dot (“..”) components.
    echo - writes the arguments to the standard output
      n: trailing newline character is not printed
      help: displays the help message and usage
    pwd - prints the name of the current working directory
      L: symbolic links are not avoided
      P: symbolic are avoided

  EXTERNAL COMMANDS:
    cat - read the contents of the file and prints its contents on the standard output
      n: number all output lines 
      E: display the $ sign at the end of each line
    date - prints the system’s date and time
      u: prints Coordinated Universal Time (UTC)
      R: prints date and time in RFC 5322 format
    ls - list the contents of the directory
      a: does not ignore system files (starting from “.”)
      A: ignores system files (starting from “.”)
    mkdir - this command makes directories
      v: prints a message for each created directory
      m: sets the file mode
    rm - removes files
      i: prompt before every file removal 
      v: explains what is being done and which file is being removed

  EDGE CASES HANDLED: 
    cd:
      No such file or directory
      Invalid command

    Echo:
      Invalid command
      Option not present

    Pwd:
      Invalid command
      Error

    Cat:
      Missing operand
      No file or directory

    Date:
      Error
      Invalid command

    Ls:
      No such file or directory
      Missing operand

    Mkdir:
      Cannot create directory
      Missing operand

    Rm:
      Cannot remove file
      Missing operand

ASSUMPTIONS:
  One command at a time in shell for easy use

THREADING:
  Type &t after command name (cat &t -n [file name])

TEST CASES:
  cat -n (filename)
  cat -E (filename)
  date -u
  date -R
  ls -a
  mkdir -v (directory name)
  rm -i (filename)
  cd -P (directory name)
  pwd -L
  Etc.
