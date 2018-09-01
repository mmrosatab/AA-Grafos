#include <ogdf/basic/Graph.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/layered/DfsAcyclicSubgraph.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
 
using namespace ogdf;
 
int main()
{
    Graph G;
 
    randomSimpleGraph(G, 3, 3); // cria grafo com 5 vértices e 5 arestas
    
    GraphAttributes GA( G, GraphAttributes::nodeGraphics | // Seta atributos do grafo
        GraphAttributes::edgeGraphics |
        GraphAttributes::nodeLabel |
        GraphAttributes::nodeStyle |
        GraphAttributes::edgeType |
        GraphAttributes::edgeArrow |
        GraphAttributes::edgeStyle ); 
    

    // nó 
    node v;

    // iterador de nós do grafo, itera de nó em nó

    forall_nodes( v, G )
    { 
        GA.fillColor( v ) = Color( "#800080" ); // vértices do grafos receberão cor roxo

        GA.height( v ) = 20.0; // setando a largura do vértice
        GA.width( v ) = 20.0; // setando a altura do vértice
 
        string s = to_string(v->index()); // converte rotulo do grafo em uma string
        char const *pchar = s.c_str();  //rotulo para cada vértice do grafo
        GA.label( v ) = pchar;
    }
 
    edge e;
    forall_edges(e ,G) // arestas do grafos receberão cor azul
    {
       // GA.bends(e);
        GA.strokeColor(e) = Color("#0000FF");
    }

    
    // 
    SugiyamaLayout SL; 
    SL.setRanking( new OptimalRanking );
    SL.setCrossMin( new MedianHeuristic );
 
    OptimalHierarchyLayout *ohl = new OptimalHierarchyLayout;
 
    SL.setLayout( ohl );
    SL.call( GA );
 
    //gerando arquivo de saída
    GraphIO::drawSVG( GA, "/home/mmrosa/Documentos/saida.svg" );
 
    return 0;
}
