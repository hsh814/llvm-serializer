#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to save data to the file specified by the environment variable
void save_data_to_file(const void *data, size_t size, const char *arg_name,
                       const char *function_name) {
  const char *filename = getenv("LLVM_SERIALIZER_FILE");
  if (!filename) {
    fprintf(stderr,
            "Error: LLVM_SERIALIZER_FILE environment variable not set.\n");
    return;
  }

  FILE *fp = fopen(filename, "ab"); // Append mode to avoid overwriting
  if (!fp) {
    perror("Error opening file");
    return;
  }

  // Write function name, argument name, and data size
  fprintf(fp, "Function: %s, Argument: %s, Size: %zu\n", function_name,
          arg_name, size);
  fwrite(data, 1, size, fp); // Write the raw data
  fprintf(fp, "\n");         // Add a separator between entries

  fclose(fp);
}

// Example instrumentation function (adapt as needed)
void instrument_pointer(void *ptr, const char *arg_name,
                        const char *function_name) {
  if (ptr) {
    save_data_to_file(ptr, sizeof(void *), arg_name,
                      function_name); // Save pointer value
  } else {
    save_data_to_file("NULL", strlen("NULL"), arg_name,
                      function_name); // Indicate null pointer
  }
}

// Add more instrumentation functions for other data types as needed...
void instrument_int(int value, const char *arg_name,
                    const char *function_name) {
  char buffer[20]; // enough space for an int
  snprintf(buffer, sizeof(buffer), "%d", value);
  save_data_to_file(buffer, strlen(buffer), arg_name, function_name);
}

// ... other instrument_ functions for different types ...