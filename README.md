# Maximum-Flow-Problem-Ford-Fulkerson-Algorithm

<b>Problem Statement:</b>

Given a single-source single-sink flow network(directed graph), find a feasible flow through the network that is maximum among all such flows.</br>
Your program must output the maximum flow possible as well as the final residual graph.

<b>Assume the following:</b></br>
1) Every edge has integral non-negative capacities.</br>
2) Every node lies on some path from source to sink.</br>

<b>Output will be evaluated on the following points:</b></br>
1) The flow returned by your program is indeed maximum.</br>
2) Flow leaving the source is equal to flow arriving at the sink in the final residual graph returned by your program.</br>
3) Flow is conserved at each node in the final residual graph returned by your program. Flow is conserved at a node when sum of all flows coming into the node is equal to sum of all flows leaving the node.

<b>Input Format:</b></br>

Code must read and write from/to stdin and stdout.</br>
Do not #define any inputs, all inputs must be taken dynamically from stdin.

First line of input will contain two space separated integers 'V' and 'E' indicating the number of nodes and edges in the flow network.</br>
'E' lines will follow each containing 3 space seperated integers describing the directed edge.</br>
First integer denotes source node of the edge.</br>
Second integer denotes destination node of the edge.</br>
Third integer denotes flow capacity of the edge.

Node 0 is the source node.</br>
Node V-1 is the sink node.

<b>Constraints:</b></br>
2 <= |V| <= 10000</br>
1 <= |E| <= 49995000</br>
Nodes are labelled from 0 to V-1.</br>
Edges are labelled from 0 to E-1.

<b>Output Format:</b>

Output contains two components.</br>
First is the integer denoting the maximum possible flow of the given input.</br>
Second is a residual graph represented in the same format as the input flow network.(Output the edges in the same order as that of the input)

<b>Sample Input:</b></br>
6 9</br>
0 1 10</br>
0 3 10</br>
1 2 4</br>
1 3 2</br>
1 4 8</br>
2 5 10</br>
3 4 9</br>
4 2 6</br>
4 5 10</br>

<b>Sample Output:</b></br>
19</br>
0 1 10</br>
0 3 9</br>
1 2 3</br>
1 3 0</br>
1 4 7</br>
2 5 9</br>
3 4 9</br>
4 2 6</br>
4 5 10</br>

<b>Explanation:</b></br>
Number of Nodes = V = 6</br>
Number of Edges = E = 9</br>

Below is the visual representation of the input flow network.</br>
<a data-flickr-embed="true"  href="https://www.flickr.com/photos/147116053@N02/29564622486/in/dateposted-public/" title="flow_network_problem"><img src="https://c7.staticflickr.com/9/8404/29564622486_c50ee9d1aa_z.jpg" width="640" height="276" alt="flow_network_problem"></a><script async src="//embedr.flickr.com/assets/client-code.js" charset="utf-8"></script></br>
Below is the final residual graph indicating the max flow.</br>
<a data-flickr-embed="true"  href="https://www.flickr.com/photos/147116053@N02/29598720085/in/dateposted-public/" title="flow_network_solved_2"><img src="https://c6.staticflickr.com/9/8010/29598720085_629431f2ab_z.jpg" width="640" height="290" alt="flow_network_solved_2"></a><script async src="//embedr.flickr.com/assets/client-code.js" charset="utf-8"></script>

<b>Output characteristics:</b></br>
1) The max flow of 19 is indeed the maximum possible.</br>
2) Flow released from source is 19, flow received at the sink is also 19.</br>
3) Flow is conserved at every node in the residual graph, i.e for each node : total incoming flow is the same as total outgoing flow.</br></br>
For example, consider node 4.</br>
  <b>Incoming flow:</b></br>
    edge 1->4 = 7</br>
    edge 3->4 = 9</br>
    Total = 16</br>
  <b>Outgoing flow:</b></br>
    edge 4->2 = 6</br>
    edge 4->5 = 10</br>
    Total = 16</br>
  Hence, flow is conserved at node 4.
