#/bin/env python3
import os
from posixpath import join
import sys
import os.path
import argparse




def write_directory(disk,directory,root):
    files = os.listdir(directory)

    split_root_path = root.split("/")
    split_root_path = list(filter(None, split_root_path))
    root_path_ = []
    last_ = ""

    for p in  split_root_path:
        last_ += "/" + p
        os.system( f"mmd -Ds -i {disk} ::" + last_ )

    for file in files:
        #print (root +"/"+file)
        os.system(f"mcopy -o -s -i  {disk} {directory}/{file} ::{root}/{file}")

def write_file(disk, file, root):
    split_root_path = root.split("/")
    split_root_path = list(filter(None, split_root_path))
    root_path_ = []
    last_ = ""

    for p in  split_root_path:
        last_ += "/" + p
        os.system( f"mmd -Ds -i {disk} ::" + last_ )

    split_root_path = file.split("/")
    split_root_path = list(filter(None, split_root_path))
    last_=root
    file1 =  root + "/" +  os.path.split(file)[1]

    for p in  split_root_path[:-1]:
        last_ += "/" + p
        os.system( f"mmd -Ds -i {disk} ::" + last_ )

    #os.system(f"mdel -i {disk} ::{file1}")
    os.system(f"mcopy -o -Ds -i  {disk} {file} ::{file1}")

def main():

    parser = argparse.ArgumentParser()

    parser.add_argument("-d","--disk", help="sets the targeted disk",required=True)
    parser.add_argument("-write-directory",action='store_true', help ="Makes chaddisker write directory to disk")
    parser.add_argument("--path", help="Path to target")
    parser.add_argument("-write-file", help="Write file to disk", action="store_true")
    parser.add_argument("--root", help="Sets the root dir to be written in")
    parser.add_argument("-list", action="store_true", help="Prints all files and directories in the root dir")

    args = parser.parse_args()

    if args.list:
        if (args.disk is not None):
            if (args.path is not None):
                os.system(f"mdir -i {args.disk} ::"+args.path)
            else:
                os.system(f"mdir -i {args.disk} ::")
                
        else:
            exit("when using -list you must also use --disk")
    elif (args.write_directory):
        if (args.path is not None and args.disk is not None):
            write_directory(args.disk, args.path,args.root)
        else:
            exit("when using -write-directory you must use --path and --disk")
    elif (args.write_file):
        if (args.path is not None and args.disk is not None and args.root is not None):
            write_file(args.disk, args.path, args.root)
        else:
            exit("when using -write-file you must use --path,--disk and --root")


main()