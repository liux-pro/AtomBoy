def binary_to_c_header(input_file, output_file, array_name):
    with open(input_file, 'rb') as f:
        binary_data = f.read()

    with open(output_file, 'w') as f:
        f.write("#ifndef {}_H\n".format(array_name.upper()))
        f.write("#define {}_H\n\n".format(array_name.upper()))

        f.write("const unsigned char {}[] = {{\n".format(array_name))
        for i, byte in enumerate(binary_data):
            f.write("0x{:02X}".format(byte))
            if i < len(binary_data) - 1:
                f.write(", ")
            if (i + 1) % 12 == 0:  # Control the number of elements per line
                f.write("\n")
        f.write("\n};\n\n")

        f.write("const unsigned int {}_size = sizeof({});\n".format(array_name, array_name))
        f.write("#endif // {}_H\n".format(array_name.upper()))

    print("Conversion completed. C header file '{}' created.".format(output_file))


if __name__ == "__main__":
    input_file_path = "ikun_basketball_compressed.bin"      # Replace 'input.bin' with your binary file path
    output_file_path = "ikun_basketball_compressed.h"        # Replace 'data.h' with your desired output header file path
    array_variable_name = "ikun_basketball_compressed"     # Replace 'binaryData' with the desired name for your C array

    binary_to_c_header(input_file_path, output_file_path, array_variable_name)
