# 💰 FinançasLab — Sistema de Controle Financeiro em C

Projeto desenvolvido para a disciplina **Laboratório de Programação**, com o objetivo de implementar um sistema de controle financeiro em linguagem C, aplicando os conceitos de manipulação de arquivos, modularização e CRUD.

---

## 📘 Sobre o Projeto

**FinançasLab** é um sistema de **controle financeiro pessoal** desenvolvido em **C**, com o objetivo de aplicar conceitos fundamentais de **estruturação de código, manipulação de arquivos e modularização**. 
O programa permite **gerenciar receitas e despesas** de diferentes usuários por meio de um **sistema CRUD completo** (criar, ler, atualizar e deletar dados), armazenando todas as informações em arquivos `.txt`.
Também realiza **cálculo automático de saldo**, geração de relatórios e **controle de orçamento**, incentivando o equilíbrio financeiro do usuário.

---

## 🎯 Objetivo Acadêmico

Trabalho desenvolvido para a disciplina **Laboratório de Programação**, com o propósito de implementar um **sistema funcional em linguagem C**, aplicando:

* Manipulação de **arquivos texto (FILE)**
* **Validação de entrada de dados**
* **Estruturas condicionais e de repetição**
* **Organização modular de código**
* **Uso de TADs simples e funções auxiliares**
* **Criação de menus e controle de fluxo**

---

## ⚙️ Funcionalidades Principais

✅ **Login e Cadastro de Usuário**

* Armazena credenciais em `dados.txt`.
* Cria automaticamente um arquivo individual de gastos (`gastos<usuario>.txt`).
* Impede duplicação de cadastro.

✅ **Registro de Receitas e Despesas**

* Armazena nome, data, valor e tipo (+ ou -).
* Atualiza automaticamente o saldo total do usuário.

✅ **Atualização e Remoção de Registros**

* Permite editar informações de despesas e receitas.
* Remove lançamentos e atualiza o saldo conforme o tipo da operação.

✅ **Relatórios e Controle de Orçamento**

* Exibe saldo atual e histórico de movimentações.
* Calcula totais de receitas e despesas.
* Retorna mensagens de incentivo ou alerta conforme o desempenho financeiro.

✅ **Validação de Entradas**

* Verifica nomes de usuários, formatos de dados e valores numéricos.
* Impede caracteres especiais e entradas incorretas.

---

## 🗂️ Estrutura de Arquivos

```
📁 Sistema_FinancasLab/
│
├── FinancasLab.c               # Código principal
├── Arquivos/
│   ├── dados.txt               # Armazena usuários e senhas
│   ├── gastos<usuario>.txt     # Arquivo de controle de cada usuário
│   └── gastosTemp.txt          # Arquivo temporário usado para atualizações
│
└── README.md                   # (este arquivo)
```

---

## 💾 Exemplo de Arquivo de Gastos

```
[1200.00]
{1 | Salário | 05/09/2025 | 3500.00 | +}
{2 | Aluguel | 10/09/2025 | 1200.00 | -}
{3 | Mercado | 15/09/2025 | 350.00  | -}
```

🟢 O valor entre **[ ]** representa o **saldo atual**.
Os valores entre **{ }** representam **transações** com:

```
ID | Nome | Data | Valor | Operação(+/-)
```

---

## 🧠 Principais Funções

| Função                | Descrição                                      |
| --------------------- | ---------------------------------------------- |
| `menu()`              | Exibe o menu inicial do sistema                |
| `logar()`             | Realiza login de usuário                       |
| `cadastrar()`         | Cria novo usuário e arquivo de gastos          |
| `addValue()`          | Registra nova receita ou despesa               |
| `gerarRelatorio()`    | Mostra o saldo e histórico de transações       |
| `atualizarDespesa()`  | Edita uma transação existente                  |
| `removerGasto()`      | Exclui uma transação e atualiza o saldo        |
| `controleOrcamento()` | Mostra análise de gastos e feedback financeiro |
| `atualizarSaldo()`    | Atualiza saldo automaticamente após operações  |

---

## 💻 Como Executar o Projeto

### 1️⃣ Compilação

Abra o terminal na pasta do projeto e compile o código:

```bash
gcc FinancasLab.c -o FinancasLab
```

### 2️⃣ Execução

Depois, execute o programa:

```bash
./FinancasLab
```

*(No Windows, use `FinancasLab.exe`)*

---

## 🔐 Fluxo de Uso

1. **Menu inicial** → Login, Cadastrar ou Sair
2. Após login → Acesso ao painel financeiro
3. **Funções disponíveis:**

   * Registrar receitas/despesas
   * Gerar relatório
   * Atualizar ou remover registros
   * Ver controle de orçamento
   * Deslogar

---

## 🧾 Exemplo de Saída

```
==== MINHAS FINANÇAS ====
Bem-vindo(a), "Nome do Usuário"
(1) Registrar receita/despesa
(2) Controle de orçamento
(3) Gerar relatório
(4) Atualizar
(5) Remover renda
(0) Deslogar

Seu saldo: R$2300.00
Receitas: 3500.00 || Despesas: 1200.00
Parabéns Mahatma pela sua disciplina financeira!
```

---

## 👥 Equipe do Trabalho

| Membros              |
| -------------------- |
| Mahatma Gandhi       |
| Ciro Coimbra         |               
| Alexsandro Martins   |
| Jeiel Lucas          |
| Rogério Pio          |

---

## 🧩 Possíveis Melhorias Futuras

* Implementar interface gráfica (GTK, ncurses ou web)
* Adicionar persistência em banco de dados (SQLite)
* Criar sistema de categorias de despesas
* Exportar relatórios em CSV ou PDF
* Suporte a múltiplos idiomas

---

## 📜 Licença

Este projeto foi desenvolvido para fins acadêmicos na disciplina de **Laboratório de Programação**.
Você pode reutilizá-lo livremente para fins de estudo e aprendizado.

---

💡 *“Controle seus gastos hoje para conquistar seus objetivos amanhã.”*
