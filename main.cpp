#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>
#include <vector>

int GRID_SIZE = 10; 
int MINE_COUNT = 10;

void clear() 
{
    std::cout << "\033[H\033[J";
}

#define RESET       "\033[0m"
#define BG_GREEN    "\033[42m"
#define RED         "\033[31m"
#define BLUE        "\033[34m"
#define CYAN        "\033[36m"
#define GREEN       "\033[32m"
#define MAGENTA     "\033[35m"
#define YELLOW      "\033[33m"
#define WHITE       "\033[37m"
#define GRAY        "\033[90m"

class Cell 
{
public:
    Cell(int column, int row)
        : column(column), row(row), reveal(false), hasMine(false), flagged(false), adjacentMines(0) {}

    Cell() : column(0), row(0), reveal(false), hasMine(false), flagged(false), adjacentMines(0) {}

    int getcolumn() const { return column; }
    int getY() const { return row; }

    bool isreveal() const { return reveal; }
    void revealCells() { reveal = true; }

    bool isFlagged() const { return flagged; }
    void toggleFlag() { flagged = !flagged; }

    bool containsMine() const { return hasMine; }
    void placeMine() { hasMine = true; }

    int getAdjacentMines() const { return adjacentMines; }
    void setAdjacentMines(int count) { adjacentMines = count; }

private:
    int column, row;
    bool reveal;
    bool hasMine;
    bool flagged;
    int adjacentMines;
};

const int AVOID_CELLS = 1;

std::string getColorForNumber(int n) {
    switch (n) {
        case 1: return BLUE;
        case 2: return GREEN;
        case 3: return RED;
        case 4: return MAGENTA;
        case 5: return YELLOW;
        case 6: return CYAN;
        case 7: return WHITE;
        case 8: return GRAY;
        default: return RESET;
    }
}

int loseGame(std::vector<std::vector<Cell>>& grid, int moves);
void fillArray(std::vector<std::vector<Cell>>& grid);
void printArray(std::vector<std::vector<Cell>>& grid);
int revealCells(std::vector<std::vector<Cell>>& grid, int column, int row, int moves);
void generateMines(std::vector<std::vector<Cell>>& grid, int mineCount, int avoidcolumn, int avoidY, int avoidCount);
void game(std::vector<std::vector<Cell>>& grid);
void flagCell(std::vector<std::vector<Cell>>& grid, int moves, int column, int row);
bool hasWon(std::vector<std::vector<Cell>>& grid, int moves);
void printTutorial();
void titleScreen(std::vector<std::vector<Cell>>& grid);
void getInput(char &condition, int &column, int &row);

int main() 
{
    std::srand(std::time(nullptr));

    std::vector<std::vector<Cell>> grid(GRID_SIZE, std::vector<Cell>(GRID_SIZE));

    titleScreen(grid);
    fillArray(grid);
    game(grid);
    return 0;
}

void titleScreen(std::vector<std::vector<Cell>>& grid) {
    int choice;

    do {
        clear();
        std::cout << "\n=========== MINESWEEPER ===========" << std::endl;
        std::cout << "1. Play" << std::endl;
        std::cout << "2. Tutorial" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Select an option (1-3): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                return;
            case 2:
                printTutorial();
                break;
            case 3:
                std::cout << "Exiting...\n";
                exit(0);
            default:
                std::cout << "Invalid input. Try again.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
        }

    } while (true);
}

void printTutorial() {
    clear();
    std::string input;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Sezione 1 - Comando di input
    std::cout << "TUTORIAL - Section 1: Command Input\n\n";
    std::cout << "To play the game, you'll input commands in this format:\n";
    std::cout << "   r 2 2\n";
    std::cout << "Where:\n";
    std::cout << "   - 'r' stands for 'reveal' (to uncover a cell)\n";
    std::cout << "   - The first number is the row (starting from 0)\n";
    std::cout << "   - The second number is the column (starting from 0)\n";
    std::cout << "\nExample:\n";
    std::cout << "   r 0 1   → Reveals the cell at row 0, column 1\n";
    std::cout << "   f 3 4   → Flags the cell at row 3, column 4 as a mine\n";
    std::cout << "\nPress Enter to continue to the next section or type 'menu' to return.\n> ";
    std::getline(std::cin, input);
    if (input == "menu") return;

    clear();

    // Sezione 2 - Meccaniche del gioco
    std::cout << "TUTORIAL - Section 2: Minesweeper Mechanics\n\n";
    std::cout << "- The goal is to uncover all cells that do NOT contain mines.\n";
    std::cout << "- Each number on the grid tells you how many mines surround that cell (in 8 directions).\n";
    std::cout << "- If you uncover a cell with 0 mines nearby, adjacent empty cells will automatically be revealed.\n";
    std::cout << "- Use the flag command (f row col) to mark potential mines.\n";
    std::cout << "- Uncovering a mine ends the game.\n";
    std::cout << "\nStrategy Tips:\n";
    std::cout << "- Start from the corners or edges.\n";
    std::cout << "- Use number clues to deduce where mines are hidden.\n";
    std::cout << "- Flag suspicious cells before uncovering near them.\n";
    std::cout << "\nPress Enter to continue or type 'menu' to return.\n> ";
    std::getline(std::cin, input);
    if (input == "menu") return;

    clear();

    // Sezione 3 - Guida con testo a sezioni
    std::cout << "TUTORIAL - Section 3: Guided Text Division\n\n";
    std::cout << "The tutorial is split into sections like this to help you focus on one concept at a time.\n";
    std::cout << "Each part introduces a new topic and waits for you to continue manually.\n";
    std::cout << "You can always type 'menu' to skip the tutorial and return to the title screen.\n";
    std::cout << "\nPress Enter to continue or type 'menu' to return.\n> ";
    std::getline(std::cin, input);
    if (input == "menu") return;

    clear();

    // Sezione 4 - Navigazione
    std::cout << "TUTORIAL - Section 4: Navigation Options\n\n";
    std::cout << "You can use the following commands during the tutorial:\n";
    std::cout << "   - Press Enter to go to the next section\n";
    std::cout << "   - Type 'menu' to exit the tutorial and return to the title screen\n";
    std::cout << "\nThese options are available in every section of the tutorial.\n";
    std::cout << "\nPress Enter to continue or type 'menu' to return.\n> ";
    std::getline(std::cin, input);
    if (input == "menu") return;

    clear();

    // Sezione 5 - Esempi pratici
    std::cout << "TUTORIAL - Section 5: Practical Gameplay Examples\n\n";
    std::cout << "Here's a sample game board after a few moves:\n\n";
    std::cout << "   0 1 2 3\n";
    std::cout << "  ---------\n";
    std::cout << "0| 1 F 1 .\n";
    std::cout << "1| 1 2 2 .\n";
    std::cout << "2| 0 0 1 F\n";
    std::cout << "3| . . . .\n\n";
    std::cout << "Legend:\n";
    std::cout << "   - Numbers: how many mines are nearby\n";
    std::cout << "   - 'F': flagged cell (suspected mine)\n";
    std::cout << "   - '.': unrevealed cell\n";
    std::cout << "\nExample Moves:\n";
    std::cout << "   r 2 0  --> Reveals a 0, auto-expands surrounding cells\n";
    std::cout << "   f 0 1  --> Flags cell (0,1) as a mine\n";
    std::cout << "   r 0 3  --> Risky move! Could be safe... or not.\n";
    std::cout << "\nUse these strategies to master the game!\n";
    std::cout << "\nPress Enter to return to the title screen.\n> ";
    std::getline(std::cin, input);
}


void printAchievements() {
    clear();
    std::cout << "ACHIEVEMENTS:\n";
    std::cout << "- Beginner: Win 1 game\n";
    std::cout << "- Veteran: Win on Hard mode\n";
    std::cout << "- Speed Demon: Win Time Attack\n\n";
    std::cout << "Press enter to return...";
    std::cin.ignore();
    std::cin.get();
}

void game(std::vector<std::vector<Cell>>& grid)
{
    int column, row;
    int moves = 0;
    char condition = 'n';

    do
    {   
        printArray(grid);
        getInput(condition, column, row);
        moves++;
        if (moves == 1)
            generateMines(grid, MINE_COUNT, column, row, AVOID_CELLS);

        int revealCellsCheck = 0; 

        if (condition == 'r')
            revealCellsCheck = revealCells(grid, column, row, moves);
        else 
        {
            flagCell(grid, moves, column, row);
            continue;
        }

        if (revealCellsCheck == 1)
            revealCells(grid, column, row, moves);
        else if (revealCellsCheck == 2) 
            return;

        if (hasWon(grid, moves))
        {
            clear();
            printArray(grid);
            std::cout << "Congratulations! You revealed all non-mine cells in " << moves << " moves." << std::endl;
            return;
        }

    } 
    while (true);
}

void getInput(char &condition, int &row, int &column) {
    std::cout << "Enter cell (r/f x y): "; // Modificato l'ordine di input

    std::cin >> condition >> row >> column; // Cambiato l'ordine di lettura
    if (std::cin.fail() || column < 0 || column >= GRID_SIZE || row < 0 || row >= GRID_SIZE || (condition != 'r' && condition != 'f')) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Please enter 'r/f y x' within the grid." << std::endl;
        getInput(condition, row, column); // Modificato l'ordine di passaggio
        return;
    }
    if (column < 0 || column >= GRID_SIZE || row < 0 || row >= GRID_SIZE)
    {
        std::cout << "Invalid input. Please enter coordinates within the grid." << std::endl;
        getInput(condition, column, row);
    }
    else if(condition != 'r' && condition != 'f') 
    {
        std::cout << "Invalid condition. Please enter 'r' to reveal or 'f' to flag." << std::endl;
        getInput(condition, column, row);
    }
}

int loseGame(std::vector<std::vector<Cell>>& grid, int moves) 
{
    clear();
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j].containsMine()) {
                grid[i][j].revealCells();
            }
        }
    }
    printArray(grid);
    std::cout << "Game Over! You hit a mine!" << " You lost in: " << moves << " moves." << std::endl;
    exit(0);
}

void fillArray(std::vector<std::vector<Cell>>& grid)
{
    for (int i = 0; i < GRID_SIZE; ++i) 
    {
        for (int j = 0; j < GRID_SIZE; ++j) 
        {
            grid[i][j] = Cell(i, j);
        }
    }
}

void printArray(std::vector<std::vector<Cell>>& grid) 
{
    clear(); // Funzione per pulire lo schermo

    // Intestazione delle colonne
    std::cout << "  ";
    for (int k = 0; k < GRID_SIZE; ++k) 
        std::cout << std::setw(3) << k;
    std::cout << "\n    ";
    for (int k = 0; k < GRID_SIZE; ++k) 
        std::cout << "___";
    std::cout << "\n";

    // Stampa della griglia
    for (int y = 0; y < GRID_SIZE; ++y) // Cambiato da 'i' a 'y'
    {
        std::cout << std::setw(2) << y << " ";

        for (int x = 0; x < GRID_SIZE; ++x) // Cambiato da 'j' a 'x'
        {
            if (grid[y][x].isreveal()) 
            {
                if (grid[y][x].containsMine())
                {
                    std::cout << "[M]";
                }
                else 
                {
                    int adj = grid[y][x].getAdjacentMines();
                    if (adj == 0)
                        std::cout << "[-]";
                    else 
                        std::cout << "[" << getColorForNumber(adj) << adj << RESET << "]";
                }
            } 
            else 
            {
                if (grid[y][x].isFlagged())
                {
                    std::cout << "[" << RED << "F" << RESET << "]";
                }
                else
                {
                    std::cout << BG_GREEN << "[ ]" << RESET;
                }
            }
        }

        std::cout << "\n    ";
        for (int k = 0; k < GRID_SIZE; ++k) 
            std::cout << "___";
        std::cout << "\n";
    }
}


int revealCells(std::vector<std::vector<Cell>>& grid, int column, int row, int moves) 
{
    // Controlla se le coordinate sono valide e se la cella è già rivelata o contrassegnata
    if (column < 0 || column >= GRID_SIZE || row < 0 || row >= GRID_SIZE || grid[row][column].isreveal() || grid[row][column].isFlagged())
        return 1;

    // Se la cella contiene una mina, il gioco è perso
    if (grid[row][column].containsMine())
    {
        loseGame(grid, moves);
        return 2;
    }

    // Rivelazione della cella attuale
    grid[row][column].revealCells();

    // Calcolo delle mine adiacenti
    int mineCount = 0;
    for (int dcolumn = -1; dcolumn <= 1; ++dcolumn) {
        for (int dy = -1; dy <= 1; ++dy) {
            // Salta la cella attuale
            if (dcolumn == 0 && dy == 0) continue;

            int ncolumn = column + dcolumn;
            int ny = row + dy;

            // Verifica se la cella adiacente è valida e contiene una mina
            if (ny >= 0 && ny < GRID_SIZE && ncolumn >= 0 && ncolumn < GRID_SIZE && grid[ny][ncolumn].containsMine())
                mineCount++;
        }
    }

    // Imposta il conteggio delle mine adiacenti nella cella attuale
    grid[row][column].setAdjacentMines(mineCount);

    // Se non ci sono mine adiacenti, riveliamo ricorsivamente le celle adiacenti
    if (mineCount == 0) 
    {
        for (int dcolumn = -1; dcolumn <= 1; ++dcolumn) 
        {
            for (int dy = -1; dy <= 1; ++dy) 
            {
                // Riveliamo solo celle adiacenti
                if (dcolumn != 0 || dy != 0)
                    revealCells(grid, column + dcolumn, row + dy, moves);
            }
        }
    }
    return 0;
}



void generateMines(std::vector<std::vector<Cell>>& grid, int mineCount, int avoidColumn, int avoidY, int avoidCount) {
    int totalCells = GRID_SIZE * GRID_SIZE;
    int count = 0;

    while (count < mineCount) {
        int column = std::rand() % GRID_SIZE;
        int row = std::rand() % GRID_SIZE;

        if (grid[row][column].containsMine())
            continue;

        bool tooClose = false;
        for (int dColumn = -avoidCount; dColumn <= avoidCount && !tooClose; ++dColumn) {
            for (int dY = -avoidCount; dY <= avoidCount && !tooClose; ++dY) {
                int nColumn = avoidColumn + dColumn;
                int nY = avoidY + dY;
                if (nColumn == column && nY == row)
                    tooClose = true;
            }
        }

        if (tooClose)
            continue;

        grid[row][column].placeMine();
        count++;
    }
}


void flagCell(std::vector<std::vector<Cell>>& grid, int moves, int column, int row) 
{
    grid[row][column].toggleFlag();
}

bool hasWon(std::vector<std::vector<Cell>>& grid, int moves) 
{
    for (int i = 0; i < GRID_SIZE; ++i) 
    {
        for (int j = 0; j < GRID_SIZE; ++j) 
        {
            if (!grid[i][j].containsMine() && !grid[i][j].isreveal()) 
            {
                return false;
            }
        }
    }
    return true;
}
