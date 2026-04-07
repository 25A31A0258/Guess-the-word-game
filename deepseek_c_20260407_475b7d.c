#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_QUESTIONS 10
#define MAX_OPTION_LEN 200
#define MAX_QUESTION_LEN 500

// Structure to hold quiz question data
typedef struct {
    char question[MAX_QUESTION_LEN];
    char options[4][MAX_OPTION_LEN];
    int correct_option; // 0-based index (0-3)
} Question;

// Function prototypes
void displayHeader();
void displayQuestion(Question q, int qNum, int totalQuestions);
int getValidatedAnswer();
void displayResult(int score, int totalQuestions);
char playAgain();
void clearScreen();

int main() {
    // Predefined quiz questions
    Question questions[] = {
        {
            "What is the capital of France?",
            {"Berlin", "Madrid", "Paris", "Lisbon"},
            2  // Paris
        },
        {
            "Which programming language is known as the 'mother of all languages'?",
            {"Python", "C", "Java", "Assembly"},
            1  // C
        },
        {
            "What is 15 × 8?",
            {"100", "110", "120", "130"},
            2  // 120
        },
        {
            "Who painted the Mona Lisa?",
            {"Van Gogh", "Picasso", "Da Vinci", "Rembrandt"},
            2  // Da Vinci
        },
        {
            "Which planet is known as the Red Planet?",
            {"Mars", "Jupiter", "Venus", "Saturn"},
            0  // Mars
        },
        {
            "What does CPU stand for?",
            {"Central Processing Unit", "Computer Personal Unit", "Central Program Utility", "Core Processing Unit"},
            0  // Central Processing Unit
        },
        {
            "Who wrote 'Romeo and Juliet'?",
            {"Charles Dickens", "Jane Austen", "William Shakespeare", "Mark Twain"},
            2  // William Shakespeare
        },
        {
            "What is the largest ocean on Earth?",
            {"Atlantic Ocean", "Indian Ocean", "Arctic Ocean", "Pacific Ocean"},
            3  // Pacific Ocean
        },
        {
            "Which year did World War II end?",
            {"1943", "1944", "1945", "1946"},
            2  // 1945
        },
        {
            "What is the square root of 144?",
            {"10", "11", "12", "13"},
            2  // 12
        }
    };
    
    int totalQuestions = sizeof(questions) / sizeof(questions[0]);
    int score, userAnswer;
    char choice;
    
    do {
        clearScreen();
        displayHeader();
        score = 0;
        
        printf("\n\t\t=== QUIZ START ===\n");
        printf("\t\tTotal Questions: %d\n", totalQuestions);
        printf("\t\tEach correct answer: +1 point\n");
        printf("\t\tNo negative marking\n\n");
        printf("\t\tPress Enter to begin...");
        getchar();
        
        // Loop through all questions
        for (int i = 0; i < totalQuestions; i++) {
            clearScreen();
            displayHeader();
            displayQuestion(questions[i], i + 1, totalQuestions);
            
            printf("\n\t\tYour answer (1-4): ");
            userAnswer = getValidatedAnswer();
            
            // Check if answer is correct (user enters 1-4, we convert to 0-3)
            if (userAnswer - 1 == questions[i].correct_option) {
                printf("\n\t\t✓ CORRECT! +1 point\n");
                score++;
            } else {
                printf("\n\t\t✗ WRONG!\n");
                printf("\t\tCorrect answer: %d. %s\n", 
                       questions[i].correct_option + 1,
                       questions[i].options[questions[i].correct_option]);
            }
            
            if (i < totalQuestions - 1) {
                printf("\n\t\tPress Enter to continue...");
                getchar();
            }
        }
        
        // Display final result
        clearScreen();
        displayHeader();
        displayResult(score, totalQuestions);
        
        // Ask to play again
        choice = playAgain();
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("\n\t\tThanks for playing! Goodbye!\n\n");
    return 0;
}

void displayHeader() {
    printf("\n\t========================================\n");
    printf("\t        MINI QUIZ GAME\n");
    printf("\t========================================\n");
}

void displayQuestion(Question q, int qNum, int totalQuestions) {
    printf("\n\tQuestion %d of %d\n", qNum, totalQuestions);
    printf("\t----------------------------------------\n");
    printf("\t%s\n", q.question);
    printf("\t----------------------------------------\n");
    
    for (int i = 0; i < 4; i++) {
        printf("\t%d. %s\n", i + 1, q.options[i]);
    }
}

int getValidatedAnswer() {
    int answer;
    char input[10];
    
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &answer) == 1 && answer >= 1 && answer <= 4) {
            return answer;
        } else {
            printf("\t\tInvalid input! Please enter a number between 1 and 4: ");
        }
    }
}

void displayResult(int score, int totalQuestions) {
    float percentage = (float)score / totalQuestions * 100;
    
    printf("\n\t\t=== QUIZ COMPLETED ===\n\n");
    printf("\t\tYour Score: %d / %d\n", score, totalQuestions);
    printf("\t\tPercentage: %.1f%%\n", percentage);
    
    printf("\n\t\tPerformance Rating:\n");
    if (percentage >= 90) {
        printf("\t\t★★★★★ Excellent! Genius level!\n");
    } else if (percentage >= 75) {
        printf("\t\t★★★★☆ Very Good! Keep it up!\n");
    } else if (percentage >= 60) {
        printf("\t\t★★★☆☆ Good! Room for improvement.\n");
    } else if (percentage >= 40) {
        printf("\t\t★★☆☆☆ Average! Practice more.\n");
    } else {
        printf("\t\t★☆☆☆☆ Need improvement! Try again.\n");
    }
}

char playAgain() {
    char choice;
    printf("\n\t\tPlay again? (y/n): ");
    scanf(" %c", &choice);
    getchar(); // Clear newline from buffer
    return choice;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}