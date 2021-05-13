import os, sys , string, random

worms_made = 0
stop = 11
patha = ''
pathb = '/'
pathc = ''
def fileworm(worms_made, stop, patha, pathb, pathc):
        filename = (''.join(random.choice(string.ascii_lowercase
        +string.ascii_uppercase + string.digits) for i in range(8)))
        pathc = patha + filename + pathb
        worms_made = worms_made +1
        os.system("mkdir %s" % filename)
        os.chdir(pathc)
        print "Worms made: %r" % worms_made
        if worms_made == stop:
                print "*Done"
                exit(0)
        elif worms_made != stop:
                pass
        fileworm(worms_made, stop, patha, pathb, pathc)
fileworm(worms_made, stop, patha, pathb, pathc)
