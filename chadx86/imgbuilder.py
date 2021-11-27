#/bin/env python3
import os
import sys
usage = """
Primum Image Builder
usage:
imgbuilder.py dir diskimg
"""
def main():
    if  len(sys.argv) < 3:
        sys.exit(usage)
    else:
        path = sys.argv[1]
        disk = sys.argv[2]
        files = os.listdir(path)
        for file in files:
            os.system(f"mcopy -o -s -i  {disk} {path}/{file} ::{file}")
                
            #for name in directories:
                #file = os.path.join(root, name)
                #os.system(f"mcopy -o -s -i {disk} {file} ::{file}")


main()