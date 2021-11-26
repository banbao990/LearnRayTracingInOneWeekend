import os

def get_include_files(path, prefix, all_files):
    file_list = os.listdir(path)
    for file in file_list:
        cur_path = os.path.join(path, file)
        prefix2 = os.path.join(prefix, file)
        if os.path.isdir(cur_path):
            get_include_files(cur_path, prefix2, all_files)
        else:
            all_files.append(prefix2)

lib = list()
get_include_files("../include/toyrender/", "", lib)
lib.sort()

remove_list = [ "All.h", "utils/rtweekend.hpp"]
filename = "../include/toyrender/All.h" 

with open(filename, "w") as f:
    f.write("#ifndef _B_ALL_H_B_\n#define _B_ALL_H_B_\n\n")
    for ele in lib:
        if(ele not in remove_list):
            f.write("#include \"" + ele + "\"\n")
    f.write("// #include \"utils/rtweekend.hpp\"\n")
    f.write("\n#endif")
