---

# string.h Assembly Implementation 🚀

Dive into the **world of assembly language** with this comprehensive project that reimagines the C standard library's `<string.h>` functions. This repository is a playground for low-level programming enthusiasts who want to explore string and memory manipulation at its core.

🔗 **Explore the Code:** [GitHub - Nalan-PandiKumar/string.h](https://github.com/Nalan-PandiKumar/string.h)

## 💡 Why This Project?

Assembly language is the ultimate test of programming skill, offering unparalleled control over the machine. By recreating `<string.h>` in assembly, this project bridges the gap between high-level programming and the raw power of the x86-32 or x86 instruction set. 

Whether you're a beginner or an advanced programmer, this project has something for everyone:
- Gain a deeper understanding of how strings and memory work.
- Learn how the C standard library functions operate under the hood.
- Optimize your low-level coding skills for performance-critical tasks.

## 🛠️ Implemented Functions

Here’s the arsenal of string and memory manipulation functions recreated in pure assembly:

### Core String Functions
- `strlen`: Determine the length of a null-terminated string.
- `strcpy`: Copy a string to another memory location.
- `strncpy`: Copy a fixed number of characters, with padding if needed.
- `strcat`: Concatenate one string onto another.
- `strncat`: Concatenate a fixed number of characters from one string to another.
- `strdup`: Create a duplicate of a string.

### Searching and Tokenizing
- `strchr`: Locate the first occurrence of a character.
- `strrchr`: Locate the last occurrence of a character.
- `strstr`: Find a substring within another string.
- `strtok`: Tokenize a string based on a delimiter.

### Comparison and Locale
- `strcmp`: Compare two strings lexicographically.
- `strncmp`: Compare a fixed number of characters.
- `strcoll`: Locale-sensitive string comparison.
- `strxfrm`: Transform a string for locale-sensitive comparisons.

### Specialized Utilities
- `strspn`: Calculate the length of the initial matching substring.
- `strcspn`: Calculate the length of the initial non-matching substring.
- `strpbrk`: Locate the first occurrence of any character from a set.
- `strerror`: Return an error description for an error code.

### Memory Management
- `memcpy`: Copy a block of memory.
- `memmove`: Copy overlapping memory blocks safely.
- `memset`: Fill memory with a specific value.
- `memcmp`: Compare two memory blocks.

## ✨ Features

- **Low-level Learning:** Grasp the fundamental operations behind string and memory manipulation.
- **Optimized Code:** Understand how to write efficient, performance-focused routines.
- **Comprehensive Coverage:** All major `<string.h>` functions, recreated in assembly.

## 📖 How to Use

1. Clone the repository:  
   ```bash
   git clone https://github.com/Nalan-PandiKumar/string.h
   cd string.h
   ```
2. Assemble and link the code using MASM or an equivalent assembler.
3. Run the executable and explore the magic of assembly.

## 🤝 Contribution

Found a bug or have an idea for improvement? Contributions are welcome! Open an issue or submit a pull request on GitHub.

---

Unleash the power of assembly with this deep dive into string handling. Happy coding!
