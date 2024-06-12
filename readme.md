## UtilCPP

A collection of useful C++ classes and functions.

### Goal

Keeping it as generic as possible, so it easily adapts to any project. Currently there are no `CC` that needs to be compiled, just include the header files and you are good to go.

### Utils

#### Classes

- `Result` - Class that holds 2 generics, a value and an error. It is used to return a value and an error at the same time.

- `Logger` - Class that is responsible for handling all kinds of logs with diffrent outcomes. You can freely define your own handle if you dont want to use our builtin: `stdio` and `fstream`

#### Macros

- `UCPP_IMPLEMENTS` - Macro that checks if a class implements a specific method.

### Installation

#### Using git

```bash
git clone https://github.com/Fabbboy/utilcpp
```

#### Using git submodule to stay up-to-date

```bash
git submodule add https://github.com/Fabbboy/utilcpp
```
