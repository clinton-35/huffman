# Huffman Coding Implementation

## Overview

This project implements Huffman Coding, a compression algorithm used to encode data efficiently. The program calculates the frequency of characters in a given text, builds a Huffman Tree, and generates optimal prefix codes for the characters. It was developed as part of a computer science assignment.

## Features

- Calculates character frequencies in a text string.
- Constructs a priority queue to build the Huffman Tree.
- Generates and displays Huffman codes for each character.
- Compresses input text by encoding it into binary representation using the generated Huffman codes.

## How to Use

1. Compile the program using a C compiler, such as `gcc`:
   ```bash
   gcc -o huffman_coding huffman_coding.c
   ```
2. Run the compiled program:
   ```bash
   ./huffman_coding
   ```
3. Enter a string of text when prompted. The program will calculate the Huffman codes and display them.

## Example

**Input:**

```
Input text for compression: example
```

**Output:**

```
Generated Huffman Codes:
e: 10
a: 110
x: 111
m: 00
p: 01
l: 1100
```

## Project Details

- **Authors:**
  - Clinton Mboloi Wambua (SCT221-0437/2023)
  - Christopher Gitau (SCT221-0280/2023)

## File Structure

- **huffman\_coding.c**: Contains the implementation of Huffman Coding.

## Concepts Used

- Data Structures: Priority Queue, Binary Tree
- Algorithms: Greedy Algorithm for building Huffman Tree
- Character Encoding

## License

This project is for educational purposes and does not include a specific license. Contact the authors for any inquiries.

