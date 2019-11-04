# Aloha.py, Python simulation example:  a form of slotted ALOHA

# here we will look finite time, finding the probability that there are
# k active nodes at epoch m

# usage:  python Aloha.py s p q m k

import random, sys

class node:  # one object of this class models one network node
   # some class variables
   s = int(sys.argv[1])  # number of nodes
   p = float(sys.argv[2])  # transmit probability
   q = float(sys.argv[3])  # msg creation probability
   activeset = []  # which nodes are active now
   inactiveset = []  # which nodes are inactive now
   r = random.Random(98765)  # set seed
   def __init__(self):  # object constructor
      # start this node in inactive mode
      node.inactiveset.append(self)
   # class methods
   def checkgoactive():  # determine which nodes will go active 
      for n in node.inactiveset:
         if node.r.uniform(0,1) < node.q:
            node.inactiveset.remove(n)
            node.activeset.append(n)
   checkgoactive = staticmethod(checkgoactive)  
   def trysend():
      numnodestried = 0  # number of nodes which have tried to send 
                         # during the current epoch
      whotried = None  # which node tried to send (last)
      # determine which nodes try to send
      for n in node.activeset:
         if node.r.uniform(0,1) < node.p:
            whotried = n
            numnodestried += 1
      # we'll have a successful transmission if and only if exactly one
      # node has tried to send
      if numnodestried == 1:
         node.activeset.remove(whotried)
         node.inactiveset.append(whotried)
   trysend = staticmethod(trysend)  
   def reset():  # resets variables after a repetition of the experiment
      for n in node.activeset:
         node.activeset.remove(n)
         node.inactiveset.append(n)
   reset = staticmethod(reset)  
            
def main():
   m = int(sys.argv[4])
   k = int(sys.argv[5])
   # set up the s nodes 
   for i in range(node.s):  node()
   count = 0
   for rep in range(10000):  
      # run the process for m epochs
      for epoch in range(m):
         node.checkgoactive()
         node.trysend()
      if len(node.activeset) == k: count += 1
      node.reset()
   print ('P(k active at time m) =', count/10000.0)

# technical device to make debugging easier, etc.
if __name__ == '__main__': main()