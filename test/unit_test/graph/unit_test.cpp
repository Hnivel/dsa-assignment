#include "unit_test.hpp"
map<string, bool (UNIT_TEST_Graph::*)()> UNIT_TEST_Graph::TESTS;

template <class T>
int intKeyHash(T &key, int capacity)
{
  return key % capacity;
}

bool charComparator(char &lhs, char &rhs)
{
  return lhs == rhs;
}
string vertex2str(char &v)
{
  stringstream os;
  os << v;
  return os.str();
}
// UPDATE
bool UNIT_TEST_Graph::graph01()
{
  string name = "graph01";
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'A', 'B', 'C', 'D'};
  for (int idx = 0; idx < 4; idx++)
  {
    model.add(vertices[idx]);
  }
  model.connect('A', 'B');
  model.connect('B', 'D');
  model.connect('C', 'B');
  model.connect('C', 'D');
  //! expect ----------------------------------
  string expect = "==================================================\n\
Vertices:   \n\
V(A, in: 0, out: 1)\n\
V(B, in: 2, out: 1)\n\
V(C, in: 0, out: 2)\n\
V(D, in: 2, out: 0)\n\
------------------------------\n\
Edges:      \n\
E(A,B,0)\n\
E(B,D,0)\n\
E(C,B,0)\n\
E(C,D,0)\n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;

  output << model.toString();

  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph02()
{
  string name = "graph02";
  //! data ------------------------------------
  UGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'A', 'B', 'C', 'D'};
  for (int idx = 0; idx < 4; idx++)
  {
    model.add(vertices[idx]);
  }
  model.connect('A', 'B');
  model.connect('B', 'D');
  model.connect('C', 'B');
  model.connect('C', 'D');

  //! expect ----------------------------------
  string expect = "==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(B, in: 3, out: 3)\n\
V(C, in: 2, out: 2)\n\
V(D, in: 2, out: 2)\n\
------------------------------\n\
Edges:      \n\
E(A,B,0)\n\
E(B,A,0)\n\
E(B,D,0)\n\
E(B,C,0)\n\
E(C,B,0)\n\
E(C,D,0)\n\
E(D,B,0)\n\
E(D,C,0)\n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;

  output << model.toString();

  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph03()
{
  string name = "graph03";
  stringstream output;
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'A', 'B', 'C', 'D', 'E'};
  for (int idx = 0; idx < 5; idx++)
  {
    model.add(vertices[idx]);
  }
  model.connect('A', 'B', 8);
  model.connect('B', 'D', 6);
  model.connect('C', 'B', 1);
  model.connect('C', 'D', 2);
  model.connect('E', 'A', 3);
  model.connect('E', 'B', 4);
  model.connect('E', 'C', 5);
  DLinkedList<char> out = model.getOutwardEdges('E');
  DLinkedList<char> in = model.getInwardEdges('B');
  output << "getOutwardEdges : E: ";
  for (auto it = out.begin(); it != out.end(); it++)
  {
    output << *it << "-> ";
  }
  output << "NULL\n";

  output << "getInwardEdges : B: ";
  for (auto it = in.begin(); it != in.end(); it++)
  {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect = "getOutwardEdges : E: A-> B-> C-> NULL\n\
getInwardEdges : B: A-> C-> E-> NULL\n\
==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(B, in: 3, out: 1)\n\
V(C, in: 1, out: 2)\n\
V(D, in: 2, out: 0)\n\
V(E, in: 0, out: 3)\n\
------------------------------\n\
Edges:      \n\
E(A,B,8)\n\
E(B,D,6)\n\
E(C,B,1)\n\
E(C,D,2)\n\
E(E,A,3)\n\
E(E,B,4)\n\
E(E,C,5)\n\
==================================================\n";

  //! output ----------------------------------

  output << model.toString();

  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph04()
{
  string name = "graph04";
  stringstream output;
  //! data ------------------------------------
  UGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'A', 'B', 'C', 'D', 'E'};
  for (int idx = 0; idx < 5; idx++)
  {
    model.add(vertices[idx]);
  }
  model.connect('A', 'B', 8);
  model.connect('B', 'D', 6);
  model.connect('C', 'B', 1);
  model.connect('C', 'D', 2);
  model.connect('E', 'A', 3);
  model.connect('E', 'B', 4);
  model.connect('E', 'C', 5);
  model.connect('E', 'E', 5);
  DLinkedList<char> out = model.getOutwardEdges('E');
  DLinkedList<char> in = model.getInwardEdges('B');
  output << "getOutwardEdges : E: ";
  for (auto it = out.begin(); it != out.end(); it++)
  {
    output << *it << "-> ";
  }
  output << "NULL\n";

  output << "getInwardEdges : B: ";
  for (auto it = in.begin(); it != in.end(); it++)
  {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect = "getOutwardEdges : E: A-> B-> C-> E-> NULL\n\
getInwardEdges : B: A-> C-> D-> E-> NULL\n\
==================================================\n\
Vertices:   \n\
V(A, in: 2, out: 2)\n\
V(B, in: 4, out: 4)\n\
V(C, in: 3, out: 3)\n\
V(D, in: 2, out: 2)\n\
V(E, in: 4, out: 4)\n\
------------------------------\n\
Edges:      \n\
E(A,B,8)\n\
E(A,E,3)\n\
E(B,A,8)\n\
E(B,D,6)\n\
E(B,C,1)\n\
E(B,E,4)\n\
E(C,B,1)\n\
E(C,D,2)\n\
E(C,E,5)\n\
E(D,B,6)\n\
E(D,C,2)\n\
E(E,A,3)\n\
E(E,B,4)\n\
E(E,C,5)\n\
E(E,E,5)\n\
==================================================\n";

  //! output ----------------------------------

  output << model.toString();

  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph05()
{
  string name = "graph05";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[3] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('C', 'D', 3.2)};
  DGraphModel<char> *model = DGraphModel<char>::create(vertices, 4, edges, 3, &charComparator, &vertex2str);

  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    DLinkedList<char> out = model->getOutwardEdges('E');
  }
  catch (const VertexNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "getOutwardEdges :E khong ton tai" << endl; // In ra thông báo lỗi
  }
  DLinkedList<char> in = model->getInwardEdges('B');

  output << "getInwardEdges : B: ";
  for (auto it = in.begin(); it != in.end(); it++)
  {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect = "Error: getOutwardEdges :E khong ton tai\n\
getInwardEdges : B: A-> NULL\n\
==================================================\n\
Vertices:   \n\
V(A, in: 0, out: 1)\n\
V(B, in: 1, out: 1)\n\
V(C, in: 1, out: 1)\n\
V(D, in: 1, out: 0)\n\
------------------------------\n\
Edges:      \n\
E(A,B,1.5)\n\
E(B,C,2)\n\
E(C,D,3.2)\n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph06()
{
  string name = "graph06";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[3] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('C', 'D', 3.2)};
  UGraphModel<char> *model = UGraphModel<char>::create(vertices, 4, edges, 3, &charComparator, &vertex2str);

  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    DLinkedList<char> out = model->getOutwardEdges('E');
  }
  catch (const VertexNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "getOutwardEdges :E khong ton tai" << endl; // In ra thông báo lỗi
  }
  DLinkedList<char> in = model->getInwardEdges('B');

  output << "getInwardEdges : B: ";
  for (auto it = in.begin(); it != in.end(); it++)
  {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect = "Error: getOutwardEdges :E khong ton tai\n\
getInwardEdges : B: A-> C-> NULL\n\
==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(B, in: 2, out: 2)\n\
V(C, in: 2, out: 2)\n\
V(D, in: 1, out: 1)\n\
------------------------------\n\
Edges:      \n\
E(A,B,1.5)\n\
E(B,A,1.5)\n\
E(B,C,2)\n\
E(C,B,2)\n\
E(C,D,3.2)\n\
E(D,C,3.2)\n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph07()
{
  string name = "graph07";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[4] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('C', 'D', 3.2),
      Edge<char>('D', 'D', 3.2)};
  UGraphModel<char> *model = UGraphModel<char>::create(vertices, 4, edges, 4, &charComparator, &vertex2str);

  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    model->weight('A', 'D');
  }
  catch (const EdgeNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "AB khong ton tai" << endl; // In ra thông báo lỗi
  }
  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    model->weight('E', 'D');
  }
  catch (const VertexNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "E khong ton tai" << endl; // In ra thông báo lỗi
  }

  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    model->weight('D', 'F');
  }
  catch (const VertexNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "F khong ton tai" << endl; // In ra thông báo lỗi
  }
  output << "AB : " << model->weight('A', 'B') << endl;
  output << "CD : " << model->weight('C', 'D') << endl;

  DLinkedList<char> in = model->getInwardEdges('D');

  output << "getInwardEdges : D: ";
  for (auto it = in.begin(); it != in.end(); it++)
  {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect = "Error: AB khong ton tai\n\
Error: E khong ton tai\n\
Error: F khong ton tai\n\
AB : 1.5\n\
CD : 3.2\n\
getInwardEdges : D: C-> D-> NULL\n\
==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(B, in: 2, out: 2)\n\
V(C, in: 2, out: 2)\n\
V(D, in: 2, out: 2)\n\
------------------------------\n\
Edges:      \n\
E(A,B,1.5)\n\
E(B,A,1.5)\n\
E(B,C,2)\n\
E(C,B,2)\n\
E(C,D,3.2)\n\
E(D,C,3.2)\n\
E(D,D,3.2)\n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph08()
{
  string name = "graph08";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[5] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('A', 'A', 10),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('C', 'D', 3.2),
      Edge<char>('D', 'D', 3.2)};
  DGraphModel<char> *model = DGraphModel<char>::create(vertices, 4, edges, 5, &charComparator, &vertex2str);

  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    model->weight('A', 'D');
  }
  catch (const EdgeNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "AB khong ton tai" << endl; // In ra thông báo lỗi
  }
  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    model->weight('E', 'D');
  }
  catch (const VertexNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "E khong ton tai" << endl; // In ra thông báo lỗi
  }

  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    model->weight('D', 'F');
  }
  catch (const VertexNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "F khong ton tai" << endl; // In ra thông báo lỗi
  }
  output << "AA : " << model->weight('A', 'A') << endl;
  output << "CD : " << model->weight('C', 'D') << endl;

  DLinkedList<char> in = model->getInwardEdges('D');

  output << "getInwardEdges : D: ";
  for (auto it = in.begin(); it != in.end(); it++)
  {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect = "Error: AB khong ton tai\n\
Error: E khong ton tai\n\
Error: F khong ton tai\n\
AA : 10\n\
CD : 3.2\n\
getInwardEdges : D: C-> D-> NULL\n\
==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 2)\n\
V(B, in: 1, out: 1)\n\
V(C, in: 1, out: 1)\n\
V(D, in: 2, out: 1)\n\
------------------------------\n\
Edges:      \n\
E(A,B,1.5)\n\
E(A,A,10)\n\
E(B,C,2)\n\
E(C,D,3.2)\n\
E(D,D,3.2)\n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph09()
{
  string name = "graph09";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[5] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('A', 'A', 10),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('C', 'D', 3.2),
      Edge<char>('D', 'D', 3.2)};
  DGraphModel<char> *model = DGraphModel<char>::create(vertices, 4, edges, 5, &charComparator, &vertex2str);
  model->remove('A');
  model->remove('B');
  DLinkedList<char> in = model->getInwardEdges('D');

  output << "getInwardEdges : D: ";
  for (auto it = in.begin(); it != in.end(); it++)
  {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect = "getInwardEdges : D: C-> D-> NULL\n\
==================================================\n\
Vertices:   \n\
V(C, in: 0, out: 1)\n\
V(D, in: 2, out: 1)\n\
------------------------------\n\
Edges:      \n\
E(C,D,3.2)\n\
E(D,D,3.2)\n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph10()
{
  string name = "graph10";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[5] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('A', 'A', 10),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('C', 'D', 3.2),
      Edge<char>('D', 'D', 3.2)};
  UGraphModel<char> *model = UGraphModel<char>::create(vertices, 4, edges, 5, &charComparator, &vertex2str);
  model->remove('B');
  model->remove('D');
  //! expect ----------------------------------
  string expect = "==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(C, in: 0, out: 0)\n\
------------------------------\n\
Edges:      \n\
E(A,A,10)\n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph11()
{
  string name = "graph11";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[5] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('A', 'A', 10),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('C', 'D', 3.2),
      Edge<char>('D', 'D', 3.2)};
  UGraphModel<char> *model = UGraphModel<char>::create(vertices, 4, edges, 5, &charComparator, &vertex2str);
  output << "Size: " << model->size() << endl;
  output << "Indegree: " << model->inDegree('A') << endl;
  output << "Outdegree: " << model->outDegree('A') << endl;
  model->remove('A');
  model->remove('B');
  model->remove('C');
  model->remove('D');
  output << "Size: " << model->size() << endl;
  try
  {
    model->inDegree('F');
  }
  catch (const VertexNotFoundException &e)
  {
    output << "Error: " << "F khong ton tai" << endl;
  }
  try
  {
    model->outDegree('F');
  }
  catch (const VertexNotFoundException &e)
  {
    output << "Error: " << "F khong ton tai" << endl;
  }
  //! expect ----------------------------------
  string expect = "Size: 4\n\
Indegree: 2\n\
Outdegree: 2\n\
Size: 0\n\
Error: F khong ton tai\n\
Error: F khong ton tai\n\
==================================================\n\
Vertices:   \n\
------------------------------\n\
Edges:      \n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph12()
{
  string name = "graph12";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[5] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('A', 'A', 10),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('C', 'D', 3.2),
      Edge<char>('D', 'D', 3.2)};
  DGraphModel<char> *model = DGraphModel<char>::create(vertices, 4, edges, 5, &charComparator, &vertex2str);
  output << "Size: " << model->size() << endl;
  output << "vertices: ";
  DLinkedList<char> a = model->vertices();
  for (auto it = a.begin(); it != a.end(); ++it)
  {
    output << *it << " ";
  }
  output << "\n";
  output << "Indegree: " << model->inDegree('A') << endl;
  output << "Outdegree: " << model->outDegree('A') << endl;
  model->remove('A');
  model->remove('B');
  model->remove('C');
  model->remove('D');
  output << "Size: " << model->size() << endl;
  try
  {
    model->inDegree('F');
  }
  catch (const VertexNotFoundException &e)
  {
    output << "Error: " << "F khong ton tai" << endl;
  }
  try
  {
    model->outDegree('F');
  }
  catch (const VertexNotFoundException &e)
  {
    output << "Error: " << "F khong ton tai" << endl;
  }
  //! expect ----------------------------------
  string expect = "Size: 4\n\
vertices: A B C D \n\
Indegree: 1\n\
Outdegree: 2\n\
Size: 0\n\
Error: F khong ton tai\n\
Error: F khong ton tai\n\
==================================================\n\
Vertices:   \n\
------------------------------\n\
Edges:      \n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph13()
{
  string name = "graph13";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'G'};

  // Định nghĩa các cạnh
  Edge<char> edges[6] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('A', 'A', 10),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('B', 'B', 2.0),
      Edge<char>('C', 'D', 3.2),
      Edge<char>('D', 'D', 3.2)};
  DGraphModel<char> *model = DGraphModel<char>::create(vertices, 8, edges, 6, &charComparator, &vertex2str);
  output << "Size: " << model->size() << endl;
  output << "vertices: ";
  DLinkedList<char> a = model->vertices();
  for (auto it = a.begin(); it != a.end(); ++it)
  {
    output << *it << " ";
  }
  output << "\n";
  output << "Indegree H: " << model->inDegree('H') << endl;
  output << "Outdegree C: " << model->outDegree('C') << endl;
  model->remove('F');
  model->remove('B');
  model->remove('H');
  model->remove('G');
  output << "Size: " << model->size() << endl;
  //! expect ----------------------------------
  string expect = "Size: 8\n\
vertices: A B C D E F H G \n\
Indegree H: 0\n\
Outdegree C: 1\n\
Size: 4\n\
==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(C, in: 0, out: 1)\n\
V(D, in: 2, out: 1)\n\
V(E, in: 0, out: 0)\n\
------------------------------\n\
Edges:      \n\
E(A,A,10)\n\
E(C,D,3.2)\n\
E(D,D,3.2)\n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph14()
{
  string name = "graph14";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'G'};

  // Định nghĩa các cạnh
  Edge<char> edges[6] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('A', 'A', 10),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('B', 'B', 2.0),
      Edge<char>('C', 'D', 3.2),
      Edge<char>('D', 'D', 3.2)};
  UGraphModel<char> *model = UGraphModel<char>::create(vertices, 8, edges, 6, &charComparator, &vertex2str);
  output << "Size: " << model->size() << endl;
  output << "vertices: ";
  DLinkedList<char> a = model->vertices();
  for (auto it = a.begin(); it != a.end(); ++it)
  {
    output << *it << " ";
  }
  output << "\n";
  output << "Indegree H: " << model->inDegree('H') << endl;
  output << "Outdegree C: " << model->outDegree('C') << endl;
  output << "connected AA : " << model->connected('A', 'A') << endl;
  output << "connected AH : " << model->connected('A', 'H') << endl;
  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    model->connected('A', 'X');
  }
  catch (const VertexNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "X khong ton tai" << endl; // In ra thông báo lỗi
  }
  try
  {
    // Gọi một phương thức có thể ném ngoại lệ
    model->connected('V', 'Q');
  }
  catch (const VertexNotFoundException &e)
  {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "V khong ton tai" << endl; // In ra thông báo lỗi
  }
  output << "Size: " << model->size() << endl;
  //! expect ----------------------------------
  string expect = "Size: 8\n\
vertices: A B C D E F H G \n\
Indegree H: 0\n\
Outdegree C: 2\n\
connected AA : 1\n\
connected AH : 0\n\
Error: X khong ton tai\n\
Error: V khong ton tai\n\
Size: 8\n\
==================================================\n\
Vertices:   \n\
V(A, in: 2, out: 2)\n\
V(B, in: 3, out: 3)\n\
V(C, in: 2, out: 2)\n\
V(D, in: 2, out: 2)\n\
V(E, in: 0, out: 0)\n\
V(F, in: 0, out: 0)\n\
V(H, in: 0, out: 0)\n\
V(G, in: 0, out: 0)\n\
------------------------------\n\
Edges:      \n\
E(A,B,1.5)\n\
E(A,A,10)\n\
E(B,A,1.5)\n\
E(B,C,2)\n\
E(B,B,2)\n\
E(C,B,2)\n\
E(C,D,3.2)\n\
E(D,C,3.2)\n\
E(D,D,3.2)\n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph15()
{
  string name = "graph15";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'G'};

  // Định nghĩa các cạnh
  Edge<char> edges[6] = {
      Edge<char>('A', 'B', 1.5),
      Edge<char>('A', 'A', 10),
      Edge<char>('B', 'C', 2.0),
      Edge<char>('B', 'B', 2.0),
      Edge<char>('C', 'D', 3.2),
      Edge<char>('D', 'D', 3.2)};
  UGraphModel<char> *model = UGraphModel<char>::create(vertices, 8, edges, 6, &charComparator, &vertex2str);
  output << "Size: " << model->size() << endl;
  output << "Indegree H: " << model->inDegree('H') << endl;
  output << "Outdegree C: " << model->outDegree('C') << endl;
  output << "contains C : " << model->contains('C') << endl;
  output << "contains J : " << model->contains('J') << endl;
  output << "Size: " << model->size() << endl;
  //! expect ----------------------------------
  string expect = "Size: 8\n\
Indegree H: 0\n\
Outdegree C: 2\n\
contains C : 1\n\
contains J : 0\n\
Size: 8\n\
==================================================\n\
Vertices:   \n\
V(A, in: 2, out: 2)\n\
V(B, in: 3, out: 3)\n\
V(C, in: 2, out: 2)\n\
V(D, in: 2, out: 2)\n\
V(E, in: 0, out: 0)\n\
V(F, in: 0, out: 0)\n\
V(H, in: 0, out: 0)\n\
V(G, in: 0, out: 0)\n\
------------------------------\n\
Edges:      \n\
E(A,B,1.5)\n\
E(A,A,10)\n\
E(B,A,1.5)\n\
E(B,C,2)\n\
E(B,B,2)\n\
E(C,B,2)\n\
E(C,D,3.2)\n\
E(D,C,3.2)\n\
E(D,D,3.2)\n\
==================================================\n\
==================================================\n\
Vertices:   \n\
------------------------------\n\
Edges:      \n\
==================================================\n";

  //! output ----------------------------------

  output << model->toString();
  model->clear();
  output << model->toString();
  delete model;
  //! remove data -----------------------------

  //! result ----------------------------------

  return printResult(output.str(), expect, name);
}

bool UNIT_TEST_Graph::graph16()
{
  stringstream output;
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
  for (int idx = 0; idx < 8; idx++)
  {
    model.add(vertices[idx]);
  }
  model.connect('1', '6');
  model.connect('1', '5');
  model.connect('1', '3');
  model.connect('4', '3');
  model.connect('3', '5');
  model.connect('5', '6');
  model.connect('5', '2');
  model.connect('8', '7');
  model.connect('6', '2');
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::DFS);

  //! expect ----------------------------------
  string expect = "DFS Topological Sort: 8->7->4->1->3->5->6->2->NULL";

  //! output ----------------------------------
  output << "DFS Topological Sort: ";
  for (auto it = result.begin(); it != result.end(); it++)
  {
    output << *it << "->";
  }
  output << "NULL";
  if (output.str() == expect)
    cout << "DFS_PASS" << endl;
  else
  {
    cout << "DFS_FAIL" << endl;
    cout << "Expect: " << expect << endl;
    cout << "Output: " << output.str() << endl;
  }
  cout << "=====================" << endl;
  //! remove data -----------------------------
  model.clear();
  return true;
}
bool UNIT_TEST_Graph::graph17()
{
  stringstream output;
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
  for (int idx = 0; idx < 8; idx++)
  {
    model.add(vertices[idx]);
  }
  model.connect('1', '6');
  model.connect('1', '5');
  model.connect('1', '3');
  model.connect('4', '3');
  model.connect('3', '5');
  model.connect('5', '6');
  model.connect('5', '2');
  model.connect('8', '7');
  model.connect('6', '2');
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::BFS);

  //! expect ----------------------------------
  string expect = "BFS Topological Sort: 1->4->8->3->7->5->6->2->NULL";

  //! output ----------------------------------
  output << "BFS Topological Sort: ";
  for (auto it = result.begin(); it != result.end(); it++)
  {
    output << *it << "->";
  }
  output << "NULL";
  if (output.str() == expect)
    cout << "BFS_PASS" << endl;
  else
  {
    cout << "BFS_FAIL" << endl;
    cout << "Expect: " << expect << endl;
    cout << "Output: " << output.str() << endl;
  }
  cout << "=====================" << endl;
  //! remove data -----------------------------
  model.clear();
  return true;
}

bool UNIT_TEST_Graph::graph18()
{
  cout << "Sort test" << endl;
  DLinkedListSE<int> testsort;
  testsort.add(11);
  testsort.add(2);
  testsort.add(1);
  testsort.add(12);
  testsort.add(5);
  testsort.add(4);
  testsort.add(10);
  testsort.add(3);
  testsort.add(8);
  testsort.add(6);
  testsort.add(9);
  testsort.add(7);
  cout << "Before sort: " << testsort.toString() << endl;
  testsort.sort();
  cout << "After sort: " << testsort.toString() << endl;
  return true;
}

bool UNIT_TEST_Graph::graph19()
{
  stringstream output;
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
  for (int idx = 0; idx < 9; idx++)
  {
    model.add(vertices[idx]);
  }

  model.connect('0', '1');
  model.connect('0', '2');
  model.connect('1', '3');
  model.connect('2', '3');
  model.connect('3', '4');
  model.connect('3', '5');
  model.connect('4', '5');
  model.connect('4', '6');
  model.connect('5', '6');
  model.connect('6', '7');
  model.connect('6', '8');
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::DFS);

  //! expect ----------------------------------
  string expect = "DFS Topological Sort: 0->2->1->3->4->5->6->8->7->NULL";

  //! output ----------------------------------
  output << "DFS Topological Sort: ";
  for (auto it = result.begin(); it != result.end(); it++)
  {
    output << *it << "->";
  }
  output << "NULL";
  if (output.str() == expect)
    cout << "DFS_PASS" << endl;
  else
  {
    cout << "DFS_FAIL" << endl;
    cout << "Expect: " << expect << endl;
    cout << "Output: " << output.str() << endl;
  }
  cout << "=====================" << endl;
  //! remove data -----------------------------
  model.clear();
  return true;
}

bool UNIT_TEST_Graph::graph20()
{
  // create test topoSorter similar to graph16 with different edges and vertices
  stringstream output;
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'1', '2', '3', '4', '5', '6'};
  for (int idx = 0; idx < 6; idx++)
  {
    model.add(vertices[idx]);
  }
  model.connect('1', '3');
  model.connect('1', '5');
  model.connect('1', '6');
  model.connect('2', '5');
  model.connect('2', '6');
  model.connect('3', '4');
  model.connect('3', '5');
  model.connect('5', '6');
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::DFS);
  string expect = "DFS Topological Sort: 2->1->3->5->6->4->NULL";
  output << "DFS Topological Sort: ";
  for (auto it = result.begin(); it != result.end(); it++)
  {
    output << *it << "->";
  }
  output << "NULL";
  if (output.str() == expect)
    cout << "DFS_PASS" << endl;
  else
  {
    cout << "DFS_FAIL" << endl;
    cout << "Expect: " << expect << endl;
    cout << "Output: " << output.str() << endl;
  }
  cout << "=====================" << endl;
  //! remove data -----------------------------
  model.clear();
  return true;
}

bool UNIT_TEST_Graph::graph21()
{
  // create test topoSorter similar to graph16 with different edges and vertices
  stringstream output;
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
  for (int idx = 0; idx < 8; idx++)
  {
    model.add(vertices[idx]);
  }
  model.connect('1', '2');
  model.connect('1', '3');
  model.connect('1', '4');
  model.connect('2', '5');
  model.connect('2', '6');
  model.connect('3', '7');
  model.connect('3', '8');
  model.connect('4', '5');
  model.connect('4', '6');
  model.connect('5', '7');
  model.connect('5', '8');
  model.connect('6', '7');
  model.connect('6', '8');
  model.connect('7', '8');
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::BFS);
  string expect = "BFS Topological Sort: 1->2->3->4->5->6->7->8->NULL";
  output << "BFS Topological Sort: ";
  for (auto it = result.begin(); it != result.end(); it++)
  {
    output << *it << "->";
  }
  output << "NULL";
  if (output.str() == expect)
    cout << "BFS_PASS" << endl;
  else
  {
    cout << "BFS_FAIL" << endl;
    cout << "Expect: " << expect << endl;
    cout << "Output: " << output.str() << endl;
  }
  cout << "=====================" << endl;
  //! remove data -----------------------------
  model.clear();
  return true;
}

bool UNIT_TEST_Graph::graph22()
{
  // create test topoSorter similar to graph16 with different edges and vertices
  stringstream output;
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'1', '2', '3', '4', '5', '6'};
  for (int idx = 0; idx < 6; idx++)
  {
    model.add(vertices[idx]);
  }
  model.connect('1', '3');
  model.connect('1', '5');
  model.connect('1', '6');
  model.connect('2', '5');
  model.connect('2', '6');
  model.connect('3', '4');
  model.connect('3', '5');
  model.connect('5', '6');
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::BFS);
  string expect = "BFS Topological Sort: 1->2->3->4->5->6->NULL";
  output << "BFS Topological Sort: ";
  for (auto it = result.begin(); it != result.end(); it++)
  {
    output << *it << "->";
  }
  output << "NULL";
  if (output.str() == expect)
    cout << "BFS_PASS" << endl;
  else
  {
    cout << "BFS_FAIL" << endl;
    cout << "Expect: " << expect << endl;
    cout << "Output: " << output.str() << endl;
  }
  cout << "=====================" << endl;
  //! remove data -----------------------------
  model.clear();
  return true;
}

bool UNIT_TEST_Graph::graph23()
{
  // create test topoSorter similar to graph16 with different edges and vertices
  stringstream output;
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'1', '2', '3', '4', '5', '6', '7'};
  for (int idx = 0; idx < 7; idx++)
  {
    model.add(vertices[idx]);
  }
  // connect graph with 7 vertices
  model.connect('1', '2');
  model.connect('1', '3');
  model.connect('2', '4');
  model.connect('2', '5');
  model.connect('3', '6');
  model.connect('3', '7');
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::DFS);
  string expect = "DFS Topological Sort: 1->3->7->6->2->5->4->NULL";
  output << "DFS Topological Sort: ";
  for (auto it = result.begin(); it != result.end(); it++)
  {
    output << *it << "->";
  }
  output << "NULL";
  if (output.str() == expect)
    cout << "DFS_PASS" << endl;
  else
  {
    cout << "DFS_FAIL" << endl;
    cout << "Expect: " << expect << endl;
    cout << "Output: " << output.str() << endl;
  }
  cout << "=====================" << endl;
  //! remove data -----------------------------
  model.clear();
  return true;
}