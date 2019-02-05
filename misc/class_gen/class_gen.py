#!/usr/bin/python

import datetime

dir = input("Directory (with trailing /): ")

while True:
    class_name = input("Class Name: ")
    if class_name == "":
            break

    hpp = open(dir+class_name+".hpp", "w+")
    cpp = open(dir+class_name+".cpp", "w+")

    cpp.write("/*\n *  Program:		{}.cpp - {} Class Implementation File\n *  Author:		    Nick Olson\n *  Date:		    {}\n *  Description:	The implementation of the {} class described in\n *                      {}.hpp, objects of which represent... \n */\n\n".format(
        class_name, class_name, datetime.datetime.now().strftime("%x"), class_name, class_name))

    hpp.write("/*\n *  Program:		    {}.hpp - {} Class Header File\n *  Author:		      Nick Olson\n *  Date:		        {}\n *  Description:	  The header file of the {} class, lists all include\n *                      statements and function prototypes for {} class.\n */\n\n".format(
        class_name, class_name, datetime.datetime.now().strftime("%x"), class_name, class_name))

    # Include statements
    cpp.write("#include \"{}.hpp\"".format(class_name))
    while True:
        while True:
            include = input("Include (with <> or \"\"): ")
            if include == "":
                break
            hpp.write("#include "+include+"\n")

        hpp.write("\nclass "+class_name+"\n{\n  private:\n")
        cpp.write("\n\n")

        # Private
        print("\n\nPrivate...")
        getters = []
        setters = []

        # Private Fields
        print("__ Fields:")
        while True:
            field = input("Field: ")
            if field == "":
                break

            maybe = input("Getter (y,n): ")
            if maybe == "y":
                getters.append(field)

            maybe = input("Setter (y,n): ")
            if maybe == "y":
                setters.append(field)

            hpp.write("    {};\n".format(field))

            print("")

        # Private Methods
        print("\n__ Methods:")
        while True:
            name = input("Name: ")
            if name == "":
                break
            return_t = input("Return Type: ")

            # Parameters
            params = []
            while True:
                param = input("Parameter: ")
                if param == "":
                    break
                params.append(param)

            # Comment
            cpp.write("/*                                                                                      -\n *  Function:   		{}::{}()\n *  Description:		a\n".format(class_name, name))
            is_first = True
            for i in range(len(params)):
                if is_first:
                    cpp.write(" *  Parameters:         ")
                    is_first = False
                else:
                    cpp.write(" *                      ")
                cpp.write(
                    "{}:\n *                          a\n".format(params[i]))
            cpp.write(" *  Returns:            _ as a {}\n *  Pre-conditions:     All fields have been instantiated.\n *  Post-conditions:    a\n */\n".format(
                return_t))

            # Function
            cpp.write("{} {}::{}(".format(return_t, class_name, name))
            hpp.write("    {} {}(".format(return_t, name))
            first = True
            for i in range(len(params)):
                if first:
                    hpp.write(params[i])
                    cpp.write(params[i])
                    first = False
                else:
                    hpp.write(", " + params[i])
                    cpp.write(", " + params[i])
            hpp.write(");\n")
            cpp.write(")\n{\n}\n")

            print("")

        hpp.write("\n  public:\n")
        cpp.write("\n")

        # Public
        print("Public...")

        # Public Fields
        print("\n__ Fields:")
        while True:
            field = input("Field: ")
            if field == "":
                break
            hpp.write("    {};".format(field))
            print("")

        # Getters and Setters
        hpp.write("\n\n    // Accessors\n")
        for i in range(len(getters)):
            t = ""
            name = getters[i].split()[len(getters[i].split())-1]
            for j in range(len(getters[i].split())-1):
                t += getters[i].split()[j] + " "
            hpp.write(
                ("    {}get_{}() {} return this->{}; {}\n").format(t, name, "{", name, "}"))
        hpp.write("\n    // Mutators\n")
        for i in range(len(setters)):
            full = setters[i]
            name = setters[i].split()[len(setters[i].split())-1]
            hpp.write(
                ("    void set_{}({}) {} this->{} = {}; {}\n").format(name, full, "{", name, name, "}"))

        # Public Methods
        hpp.write("\n    // General\n")
        print("__ Methods:")
        while True:
            name = input("Name: ")
            if name == "":
                break
            return_t = input("Return Type: ")

            # Parameters
            params = []
            while True:
                param = input("Parameter: ")
                if param == "":
                    break
                params.append(param)

            # Comment
            cpp.write("/*                                                                                      -\n *  Function:   		{}::{}()\n *  Description:		a\n".format(class_name, name))
            is_first = True
            for i in range(len(params)):
                if is_first:
                    cpp.write(" *  Parameters:         ")
                    is_first = False
                else:
                    cpp.write(" *                      ")
                cpp.write(
                    "{}:\n *                          a\n".format(params[i]))
            cpp.write(" *  Returns:            _ as a {}\n *  Pre-conditions:     All fields have been instantiated.\n *  Post-conditions:    \n */\n".format(
                return_t))

            # Function
            cpp.write("{} {}::{}( ".format(return_t, class_name, name))
            hpp.write("    {} {}( ".format(return_t, name))
            first = True
            for i in range(len(params)):
                if first:
                    hpp.write(params[i])
                    cpp.write(params[i])
                    first = False
                else:
                    hpp.write(", " + params[i])
                    cpp.write(", " + params[i])
            hpp.write(" );\n")
            cpp.write(" )\n{\n}\n")

            print("")

        hpp.write("};\n\n")

    hpp.close()
    cpp.close()
