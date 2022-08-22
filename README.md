# Minishell

### [C]

### Implementation of a basic shell

This group project was done with JuPillet. The goal was to implement a small shell following Bash as reference. Reading Bash's documentation was a valid approach, but we opted for reverse engineering to replicate the behaviors ourselves.


#### The subject requiered to implement several builtins:

- **cd** with only a relative or absolute path
- **echo** with option -n
- **env** with no options
- **exit** with no options
- **export** with no options
- **pwd** with no options
- **unset** with no options


#### The following functionalities where required:

- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the **PATH** variable or using a relative or an absolute path).
- Not use more than one global variable.
- Not interpret unclosed quotes or special characters which are not required by the subject such as `\` or `;` .
- Handle `’` which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- Handle `"` which should prevent the shell from interpreting the meta-characters in the quoted sequence except for `$`.

- `<` should redirect input.
- `>` should redirect output.
- `<<` heredoc.
- `>>` should redirect output in append mode.

- Implement pipes `|`.
- Handle environment variables which should expand to their values.
- Handle `$?`.
- Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.


#### Skills gained:

Through this project, we have developed teamwork skills, learned how to get along, analyze and imagine how things work under the hood. At first, it was difficult, but we arrived at the end with an outcome that is very satisfactory for us.

![alt text](https://i.imgur.com/wtxZeF1.png "Final grade 100/100")
