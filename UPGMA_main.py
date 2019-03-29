import subprocess

def main():
    end = False
    file_name = "3.in"

    while (not end):
        print("(1) Overwrite file (next choose 2 to add it it)")
        print("(2) Add to sequence file")
        print("(3) Run UPGMA phylogenic tree construction")
        print("(4) Exit")

        choice = input("Enter choice: ")

        if (choice == "4"):
            end = True

        elif (choice == "1"):
            fh = open("cmake-build-debug/" + file_name, "w")
            name = input("Enter sequence name: ")
            sequence = input("Enter sequence of 15 characters: ")
            while (len(sequence) < 15):
                sequence = input("Enter sequence of 15 characters: ")

            fh.write("\n>" + name + "\n")
            fh.write(sequence + "\n")

            fh.close()
        elif (choice == "2"):
            fh = open("cmake-build-debug/" + file_name, "a")
            name = input("Enter sequence name: ")
            sequence = input("Enter sequence of 15 characters: ")
            while (len(sequence) < 15):
                sequence = input("Enter sequence of 15 characters: ")
            fh.write("\n>" + name + "\n")
            fh.write(sequence + "\n")

            fh.close()

        elif (choice == "3"):
            p = subprocess.call('gcc -std=c++1y -c main.cpp', stdin=None, stdout=None, stderr=None, shell=True)
            p = subprocess.call('gcc -std=c++1y -c Tree.cpp', stdin=None, stdout=None, stderr=None, shell=True)

            if p != 0:
                print('C++ compile errors')
            else:
                subprocess.call('g++ -o output.out main.o Tree.o', stdin=None, stdout=None, stderr=None, shell=True)
                print(subprocess.Popen('./output.out', shell=True, stdout=subprocess.PIPE, stdin=subprocess.PIPE, universal_newlines=True).stdout.read().rstrip())


    else:
            choice = input("Try again: ")

    print(choice)

main()