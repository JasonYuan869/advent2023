#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define INDEX(row, col) (m * (row) + (col))
#define IS_NUMERIC(ch) ('0' <= (ch) && (ch) <= '9')

// Sorted clockwise from the top left
const int DIRECTION_VECTORS[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};

int part1(int m, int n, const char* schematic)
{
  int ret = 0;
  char num_buffer[8];
  int buffer_index = 0;
  bool valid = false;
  for (int row = 0; row < m; row++) {
    if (buffer_index != 0 && valid) {
      num_buffer[buffer_index++] = '\0';
      ret += atoi(num_buffer);
      valid = false;
    }
    buffer_index = 0;

    for (int col = 0; col < n; col++) {
      char ch = schematic[INDEX(row, col)];

      if (IS_NUMERIC(ch)) {
        num_buffer[buffer_index++] = ch;

        // Check 8 directions
        for (int i = 0; i < 8 && !valid; i++) {
          int row_to_check = row + DIRECTION_VECTORS[i][0];
          int col_to_check = col + DIRECTION_VECTORS[i][1];
          if (col_to_check >= m || col_to_check < 0 ||
              row_to_check >= n || row_to_check < 0) {
            continue;
          }

          char symbol_to_check = schematic[INDEX(row_to_check, col_to_check)];
          if (!IS_NUMERIC(symbol_to_check) && '.' != symbol_to_check) {
            valid = true;
          }
        }
      } else {
        if (buffer_index == 0)
          continue;

        if (valid) {
          num_buffer[buffer_index++] = '\0';
          ret += atoi(num_buffer);
          valid = false;
        }
        buffer_index = 0;
      }
    }
  }
  return ret;
}

int part2(int m, int n, char* schematic)
{
  int ret = 0;
  char num_buffer[8];
  int buffer_index = 0;

  for (int row = 0; row < m; row++) {
    for (int col = 0; col < n; col++) {
      char ch = schematic[INDEX(row, col)];

      if ('*' != ch)
        continue;

      int gear_ratio = 1;
      int adj_gear_count = 0;
      bool checked[3][3] = {false};

      // Look for adjacent numbers
      for (int i = 0; i < 8; i++) {
        int row_rel = DIRECTION_VECTORS[i][0];
        int col_rel = DIRECTION_VECTORS[i][1];

        if (checked[row_rel+1][col_rel+1])
          continue;

        checked[row_rel+1][col_rel+1] = true;

        int row_to_check = row + row_rel;
        int col_to_check = col + col_rel;
        if (col_to_check >= m || col_to_check < 0 ||
            row_to_check >= n || row_to_check < 0) {
          continue;
        }

        char symbol = schematic[INDEX(row_to_check, col_to_check)];
        if (IS_NUMERIC(symbol)) {
          // Backtrack until first digit
          while (col + col_rel - 1 >= 0) {
            symbol = schematic[INDEX(row_to_check, col + col_rel - 1)];
            if (!IS_NUMERIC(symbol))
              break;

            col_rel--;
          }

          // Read number into num_buffer and mark certain indices as "checked", as necessary
          while (col + col_rel < n) {
            symbol = schematic[INDEX(row_to_check, col + col_rel)];
            if (!IS_NUMERIC(symbol))
              break;

            num_buffer[buffer_index++] = symbol;
            if (-1 <= col_rel && col_rel <= 1) {
              checked[row_rel+1][col_rel+1] = true;
            }

            col_rel++;
          }
          num_buffer[buffer_index++] = '\0';
          gear_ratio *= atoi(num_buffer);
          buffer_index = 0;
          adj_gear_count++;
        }
      }

      if (adj_gear_count == 2) {
        ret += gear_ratio;
      }
    }
  }

  return ret;
}


int main(int argc, char* argv[])
{
  if (argc < 2) {
    return -1;
  }

  char* path = argv[1];

  // The actual input is only 140 * 140 + 1 characters, but we allocate some more to support larger inputs
  // m-by-n row major buffer to store the schematic read from the file
  int m = 0, n;
  char* buffer = malloc(sizeof(char) * 256 * 256);

  FILE* input = fopen(path, "r");

  char* window = buffer;
  if (!fgets(window, 256, input)) {
    return -1;
  }
  n = strlen(buffer) - 1; // don't count newline
  window += n;
  m += 1;
  while (fgets(window, 256, input)) {
    window += n;
    m += 1;
  }
  fclose(input);

  printf("%d\n", part1(m, n, buffer));
  printf("%d\n", part2(m, n, buffer));

  free(buffer);
}
