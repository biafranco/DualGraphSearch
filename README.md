# 📦 Nome do Projeto: DualGraphSearch

Trabalho prático de Estruturas de Dados que implementa dois algoritmos clássicos de caminhos mínimos (**Dijkstra** e **A\***) sobre dois tipos de representação de grafos: **lista de adjacência** e **matriz de adjacência**. O problema simula um herói tentando chegar até seu destino em um mapa com portais, energia limitada e limites no uso de portais.

---

## 📁 Estrutura do Projeto

```
.
├── src/              # Código-fonte (main.cpp, classes de grafo, heurística)
├── include/          # Arquivos de cabeçalho
├── bin/              # Executável gerado
├── obj/              # Objetos compilados
├── input.txt         # Arquivo de entrada padrão
├── output.txt        # Arquivo de saída com resultados
├── Makefile          # Automação da compilação
└── README.md         # Você está aqui
```

---

## ⚙️ Compilar e executar

1. Compile o projeto usando o Makefile:

```bash
make
```

2. Execute o programa passando o input e redirecionando para a saída:

```bash
./bin/main < input.txt > output.txt
```

---

## 📥 Formato de entrada (`input.txt`)

- Primeira linha: `N M K`  
  - `N` = número de vértices  
  - `M` = número de arestas (caminhos normais)  
  - `K` = número de portais  

- Próximas `N` linhas: `x y`  
  - Coordenadas dos vértices (para heurística do A*)  

- Próximas `M` linhas: `u v custo`  
  - Caminhos normais com custo  

- Próximas `K` linhas: `u v`  
  - Portais entre vértices  

- Última linha: `E P`  
  - `E` = energia do herói  
  - `P` = máximo de portais que podem ser usados

---

## 📤 Formato de saída (`output.txt`)

- Custo mínimo usando Dijkstra com matriz
- Custo mínimo usando A* com matriz
- Custo mínimo usando Dijkstra com lista
- Custo mínimo usando A* com lista

**Exemplo:**

```
Dijkstra (matriz): 12
A*       (matriz): 10
Dijkstra (lista) : 12
A*       (lista) : 10
```

---

## 🧠 Algoritmos

- **Dijkstra**: algoritmo clássico de caminhos mínimos em grafos com pesos não-negativos.
- **A\***: algoritmo heurístico que utiliza distância euclidiana como função de avaliação.

### Representações utilizadas:
- Lista de adjacência
- Matriz de adjacência

---

## 👩‍💻 Autor

**Bianca Franco**  
Aluna de Sistemas de Informação — UFMG  
📧 contato.biancafranco@gmail.com  
🔗 [github.com/biafranco](https://github.com/biafranco)

---

## 📝 Licença

Projeto acadêmico sem fins comerciais, desenvolvido como trabalho prático da disciplina de Estruturas de Dados.
