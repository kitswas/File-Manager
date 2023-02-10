# File-Manager

## Introduction

This is a simple Cross-platform file manager written in C++ leveraging the power of Qt 6. This project was made for a certain Undergraduate course.  
We welcome all to explore the codebase to learn more about Qt and C++.

The software is not meant for general use. It is a proof of concept and does not take into account User Experience.

*Warranty **not** included.* Use it at your own risk.

![Screenshot](https://user-images.githubusercontent.com/90329875/218097518-b68c261e-847b-4f4a-a2c9-0ee7f2483ca9.png)

## Setting up your development environment

See the [Setup Guide](Setup_Guide.md).

## Generating Documentation

This project uses [Doxygen](https://www.doxygen.nl/index.html) to generate documentation.  
If Doxygen is available on your system,  
You can generate the documentation by running the following command:

```bash
doxygen Doxyfile
```

Once done, you can open the generated documentation by opening the [`docs/index.html`](docs/index.html) file in your browser.

This repository has automated workflow via Github Actions. Documentation is auto-generated.  
Disable Actions on your own fork or delete the [workflows](./.github/workflows) folder if you do not want to be billed.  
This is **not my responsiblity.**
