# assembler-and-emulator

![Banner](https://capsule-render.vercel.app/api?type=venom&height=300&color=timeGradient&text=Assembler%20and%20Emulator&section=header&reversal=false&textBg=false&fontColor=ffffff&fontSize=60&desc=CO%20Project%20CSE_112_2025&descSize=15&descAlignY=63&descAlign=81)

![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Linux](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![AssemblyScript](https://img.shields.io/badge/assembly%20script-%23000000.svg?style=for-the-badge&logo=assemblyscript&logoColor=white)

Repository for Computer Organization, Winter 2025 semester, assignment at IIITD.

## Usage

In order to use this project to assemble code please follow the following instructions.

### installing requirements

- nasm assembler.
- cmake build system.
- gcc/msvc compiler.

### build project and compile source code

make the project files and build using build system

```bash
cmake -S . -B build
cd build
make
```

this should compile source code into `SimpleAssembler.exe`

### use assembler

to use this assembler write commond in specified manner

```bash
SimpleAssembler -file source.asm -out source.exe -rel
```

`-rel` flag can be changed with `-abs` to select between relative and absolute path.

## Contributors

- [Mohd Zaid](https://github.com/MohdZaid0205)
- [Rishabh Gupta](https://github.com/RishabhGuptaGH)
- [Sambhav Jain](https://github.com/Sambhav2415)
- [Shlok Gupta](https://github.com/Th3D3stroy3r)
