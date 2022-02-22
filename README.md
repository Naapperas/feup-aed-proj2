# feup-aed-proj2

# Algorithms and Data Structures Project


This repository holds the files submitted for the 2nd AED project.

---

## Project group 13:
- up202007865, [Nuno Pereira](https://github.com/Naapperas)<br>
- up202004714, [Pedro Nunes](https://github.com/pedronunes19)<br>
- up202004724, [Vítor Cavaleiro](https://github.com/Cavaleiro132)<br>

## Project grade: 20/20

## Proposed problem

The problem proposed for this project was for us to build a tool to aid in the choice of route between 2 locations on a bus network (based on real data), using for that a graph data structure. The project specification got deeper in explaining the intended features to implement (defining "locations" as a network node/coordinate pair, various definitions of "best-route", etc...). Of those, the only one that was not achieved was the **"best route using the least bus line changes"**.

This is due to the fact that the dataset given to us, being processed "as is" (just like we did), creates a multi-graph, which in turn makes it impossible to discover the **"best route using the least bus line changes"**, since this would require analysis of every outwards edge on every node along the path between the 2 chosen points, which would not only waste a lot of memory but is also absurdly time-consuming. A solution to this problem is not to store each "real-world" node as a graph node but every "node/edge-identifier" pair as the node. This way one would lose the multi-graph, allowing to more efficiently traverse the desired nodes.

Despite this, we have implemented features that were marked as "extra credits".

## Disclaimer

This repository (and all others with the name format `feup-*`) are for archival and educational purposes only.

If you don't understand some part of the code or anything else in this repo, feel free to ask (although I may not understand it myself anymore).

Keep in mind that this repo is public. If you copy any code and use it in your school projects you may be flagged for plagiarism by automated tools.
