# File-Manager

## Introduction

This is a simple Cross-platform file manager written in C++ leveraging the power of Qt 6. This project was made for a certain Undergraduate course.  
We welcome all to explore the codebase to learn more about Qt and C++.

[The source](https://github.com/kitswas/File-Manager) is licensed under [GPLv3](https://github.com/kitswas/File-Manager/blob/main/LICENSE.TXT).

The software is not meant for general use. It is a proof of concept and does not take into account User Experience.  
This project neither promises to be fully functional, nor aims to compete with the various open-source File Managers out there.  
Use them, not this, if you need something for general/daily use.

*Warranty **not** included.* Use it at your own risk.

![Screenshot](https://github.com/kitswas/kitswas/assets/90329875/707759c8-1661-4993-ac97-7f2eda09f0a0)  
*Screenshot showing the File Manager application (build [a4a18b6](https://github.com/kitswas/File-Manager/commit/a4a18b6a0c375ef03e0a6ee4329fe96cd4254d9c)) with an open search dialog running in Windows 11.*

## Setting up your development environment

See the [Setup Guide](Setup_Guide.md).

## Online Builds

You can now build and run the project online using GitHub Actions.  
Head over to [kitswas/File-Manager-Builds](https://github.com/kitswas/File-Manager-Builds) and follow the instructions.

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
