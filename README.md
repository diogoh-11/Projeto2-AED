# Trabalho de Algoritmos em Grafos

## Descrição

Este projeto tem como objetivo desenvolver algoritmos para grafos com ou sem  pesos associados aos arcos, além de analisar a eficiência computacional das estratégias desenvolvidas. Os algoritmos implementados deverão realizar operações fundamentais sobre grafos direcionados e não direcionados.

## Módulos

1. **TAD GRAPH**  
   Desenvolve a funcionalidade que, dado um grafo orientado, constrói o correspondente grafo orientado transposto.

2. **Módulo BELLMAN-FORD**  
   Implementa o algoritmo de Bellman-Ford, que permite calcular a árvore de caminhos mais curtos de um vértice fonte até todos os demais vértices alcançáveis em um grafo orientado com pesos associados aos arcos.

3. **Módulo TRANSITIVE-CLOSURE**  
   Desenvolve a funcionalidade que, dado um grafo orientado, determina o fecho transitivo do grafo, identificando os vértices alcançáveis de cada vértice. Esta funcionalidade é implementada com base no algoritmo de Bellman-Ford.

4. **Módulo ALL-PAIRS-SHORTEST-DISTANCES**  
   Construi uma matriz de distâncias para um grafo orientado com pesos associados aos arcos, indicando a menor distância entre todos os pares de vértices, sempre que exista um caminho. Os cálculos são baseados no módulo BELLMAN-FORD.

5. **Módulo Extra - ECCENTRICITY-MEASURES**  
   Desenvolver funcionalidades adicionais para determinar:
   - A **excentricidade** de cada vértice.
   - O **raio** do grafo (menor excentricidade entre os vértices).
   - O **diâmetro** do grafo (maior excentricidade entre os vértices).
   - O **conjunto de vértices centrais**.

   Estas funcionalidades foram implementadas utilizando o módulo ALL-PAIRS-SHORTEST-DISTANCES.

## Compilar

O projeto inclui um arquivo `Makefile` para facilitar a compilação de todos os programas. O comando principal é:

```bash
make
```

### Principais Alvos

- **all**: Compila todos os programas principais descritos em `TARGETS`.
- **clean**: Remove todos os arquivos objeto (`.o`) e binários gerados durante a compilação.

### Programas Compilados

Os principais programas que podem ser gerados são:
- `TestAllPairsShortestDistances`
- `TestBellmanFordAlg`
- `TestCreateTranspose`
- `TestEccentricityMeasures`
- `TestTransitiveClosure`

Cada programa depende de módulos específicos, como `Graph.o`, `GraphBellmanFordAlg.o`, entre outros, para organizar a estrutura e as funcionalidades dos algoritmos em grafos.

