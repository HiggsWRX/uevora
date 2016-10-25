def q(s):
    l = s.split(" ")
    f = True
    ns = ""
    for i in range(len(l)):
        if l[i].isupper():
            f = True
            ns += l[i]
        elif l[i].islower():
            f = False
            ns += l[i] + " "
        else:
            if f == True:
                r = (float(l[i]) - 50) / 50
                r  = "{0:.3f}".format(r)
                ns += r + " "
            else:
                r = float(l[i]) / 50
                r  = "{0:.3f}".format(r)
                ns += r + " "
    return ns