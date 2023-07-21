# 虽然看不懂算法,但是maxigo需要一个很大的数组,用来参与计算,这个数组是只读的
# 这个数组7380字节,但是里面大部分是0,完全可以只记录有用的字节,然后再运行时再初始化.
# 这个脚本就是挑出来非零的数据
# 气死我了,这么搞内存又不够了. 算了
import re

with open("maxigo/threatstable24.h") as fo:
    read = fo.read()
    findall = re.findall(r"0x\w+", read)

    hex_map = {}
    for i, x in enumerate(findall):
        if x != "0x00":
            if x not in hex_map:
                hex_map[x] = [i]
            else:
                hex_map[x].append(i)

    for key, value in hex_map.items():
        print(f"Key: {key}, Value: {value}")


    def build_c_code(hex_value: str, position: list):
        s = f"const static uint16_t hex_{hex_value}_value_position[] __attribute__((section(\".data_flash\")))  = {{"
        s = s + ",".join([str(item) for item in position])
        s = s + "};"
        s = s + f'''   
         for (int i = 0; i < sizeof(hex_{hex_value}_value_position); ++i) {{
            _black_threats24[hex_{hex_value}_value_position[i]] = {hex_value};
           }}
        '''
        print(s)
        return s


    code = ""
    for key, value in hex_map.items():
        code = code + build_c_code(key, value)
    with open("initThreads.init", "w") as fw:
        fw.write(code)

    print(len(findall))
