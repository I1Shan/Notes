#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_CONTENT_LENGTH 1000
#define MAX_NOTES 100


typedef struct {
    char title[MAX_TITLE_LENGTH];
    char content[MAX_CONTENT_LENGTH];
} Note;

// Глобальный массив для хранения заметок
Note notes[MAX_NOTES]; // Предположим, что может быть до 100 заметок

// Глобальная переменная для отслеживания количества созданных заметок
int noteCount = 0;

/*
void createNote(const char *title, const char *content);
int noteExists(const char *title);
void editNote(const char *title);
void deleteNote(const char *title);
void viewNote(const char *title);
void listNotes();
void searchNotes(const char *keyword);
void importNotes(const char *filename);
void exportNotes(const char *filename);
void exitProgram(int numNotesCreated, int numNotesDeleted);

int main(){
	int numNotesCreated = 0;
    int numNotesDeleted = 0;
	char symbol;
    char title[50];
    char content[500];

    do {
        printf("Введите символ (l - список заметок, c - создать новую заметку, v - просмотр заметки, e - редактирование заметки, d - удаление заметки, q - выход): ");
        scanf(" %c", &symbol);

        switch (symbol) {
            case 'l':
                listNotes();
                break;
            case 'c':
                printf("Введите заголовок новой заметки: ");
                scanf(" %s", title);
                printf("Введите содержимое новой заметки: ");
                scanf(" %[^\n]%*c", content);
                createNote(title, content);
				numNotesCreated++;
                break;
            case 'v':
                printf("Введите заголовок заметки для просмотра: ");
                scanf(" %s", title);
                viewNote(title);
                break;
            case 'e':
                printf("Введите заголовок заметки для редактирования: ");
                scanf(" %s", title);
                editNote(title);
                break;
            case 'd':
                printf("Введите заголовок заметки для удаления: ");
                scanf(" %s", title);
                deleteNote(title);
				numNotesDeleted++;
                break;
            case 'q':
                exitProgram();
                break;
            default:
                printf("Некорректный символ.\n");
                break;
        }

        printf("\n");

    } while (symbol != 'q');
	return 0;
}
*/
void createNote(const char *title, const char *content) {
    // Проверяем, не превышено ли максимальное количество заметок
    if (noteCount >= MAX_NOTES) {
        printf("Error: Exceeded the maximum number of notes.\n");
        return;
    }

    // Проверяем длину заголовка и содержимого
    if (strlen(title) > MAX_TITLE_LENGTH || strlen(content) > MAX_CONTENT_LENGTH) {
        printf("Error: The maximum length of the title or content has been exceeded.\n");
        return;
    }

    // Создаем новую заметку и добавляем ее в массив
    strcpy(notes[noteCount].title, title);
    strcpy(notes[noteCount].content, content);
    noteCount++;

    printf("Note successfully created .\n");
}

int noteExists(const char *title) {
	int note_index = -1;
	for (int i = 0; i < noteCount; i++) {
        if (strstr(notes[i].title, title) != NULL) {
            note_index = i;
            break;
        }
    }

    if (note_index == -1) {
        printf("Note with the name '%s' not found.\n", title);
    }
	return note_index;
}

void editNote(const char *title) {
	// Найти заметку с указанным названием
    int note_index = noteExists(title);
    // Запросить новое содержание заметки
	if (note_index != -1) {
		printf("Enter the new content of the note with the title '%s':\n", title);
		fgets(notes[note_index].content, sizeof(notes[note_index].content), stdin);
		printf("Note successfully edited.\n");
	}
}

void deleteNote(const char *title) {
	int found = 0;
    int i = noteExists(title);
    if (i != -1) {
        // Заметка найдена, удаляем её
        for (int j = i; j < noteCount - 1; j++) {
            // Сдвигаем оставшиеся заметки влево
            strcpy(notes[j].title, notes[j + 1].title);
            strcpy(notes[j].content, notes[j + 1].content);
        }
        noteCount--;
        found = 1;
    }
    if (found) {
        printf("The note with the title \"%s\" has been deleted.\n", title);
    } else {
        printf("The note with the title \"%s\" was not found.\n", title);
    }
}

void viewNote(const char *title) {
    int i = noteExists(title);
    if (i != -1) {
		printf("Title of the note: %s\n", notes[i].title);
		printf("Note contents:\n%s\n", notes[i].content);
    } else {
        printf("Note with the title \"%s\" not found.\n", title);
        return;
	}    
}

void listNotes() {
    if (noteCount == 0) {
        printf("There are no notes to display.\n");
        return;
    }

    printf("List of notes:\n");
    for (int i = 0; i < noteCount; i++) {
        printf("Note %d:\n", i + 1);
        printf("Title: %s\n", notes[i].title);
        printf("Content: %s\n", notes[i].content);
        printf("-------------------\n");
    }
}

void searchNotes(const char *keyword) {
    int found = 0;

    printf("Keyword search result '%s':\n", keyword);
    for (int i = 0; i < noteCount; i++) {
        // Проверить наличие ключевого слова в названии или содержимом заметки
        if (strstr(notes[i].title, keyword) != NULL || strstr(notes[i].content, keyword) != NULL) {
            printf("Note %d:\n", i + 1);
            printf("Title: %s\n", notes[i].title);
            printf("Content: %s\n", notes[i].content);
            printf("-------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Notes with the keyword \"%s\" were not found.\n", keyword);
    }
}

void importNotes(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening error: %s\n", filename);
        return;
    }
	
    // Построчное чтение файла и заполнение массива заметок
    int feof = 0;
    while (!feof) {
		char title[MAX_TITLE_LENGTH];
		char content[MAX_CONTENT_LENGTH];
		if (fgets(title, MAX_TITLE_LENGTH, file) == NULL) {
            feof = 1; // Reached end of file or error occurred
            break;
        }
		size_t title_length = strlen(title);
		//printf("\nTHIS IN THE END:%c|", title[title_length - 1]);
        if (title_length > 0 && title[title_length - 1] == '\n') {
            title[title_length - 1] = '\0'; // Replace '\n' with '\0'
        }
		//printf("\nAFTER REPLACING THIS IN THE END:%c|", title[title_length - 1]);
        if (fgets(content, MAX_CONTENT_LENGTH, file) == NULL) {
            feof = 1; // Reached end of file or error occurred
            break;
        }
		size_t content_length = strlen(content);
        if (content_length > 0 && content[content_length - 1] == '\n') {
            content[content_length - 1] = '\0'; // Replace '\n' with '\0'
        }
		if (title != NULL && content != NULL) {
			if (noteCount >= MAX_NOTES) {
				printf("The maximum number of notes has been reached. The import is completed.\n");
				break;
			}
			//printf("Title: %s\n", title);  //DELETE LATER
			//printf("Content: %s\n", content);
			strcpy(notes[noteCount].title, title);
			strcpy(notes[noteCount].content, content);
			noteCount++;
        } else feof = 1;
    }
    fclose(file);
}

void exportNotes(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening a file for writing: %s\n", filename);
        return;
    }
    // Запись заметок в файл
    for (int i = 0; i < noteCount; i++) {
        fprintf(file, "Title: %s\nContent: %s\n\n", notes[i].title, notes[i].content);
    }

    fclose(file);
    printf("Notes have been successfully exported to the file: %s\n", filename);
}

void exitProgram(int numNotesCreated, int numNotesDeleted) {
    printf("Termination of the program.\n");
    printf("Number of notes written by the user: %d\n", numNotesCreated);
    printf("Number of notes deleted by the user: %d\n", numNotesDeleted);
	printf("Total notes: %d\n", noteCount);
}

int main(){
	int numNotesCreated = 0;
    int numNotesDeleted = 0;
	char symbol;
    char title[MAX_TITLE_LENGTH];
    char content[MAX_CONTENT_LENGTH];
	char filename[256];
    char keyword[50];

    do {
        printf("Enter the character: \nl - list of notes, c - create a new note,\
\nv - view a note, e - edit a note, \nd - delete a note, s - search for notes,\
\nn - import notes, x - export notes, q - exit\n");
        scanf(" %c", &symbol);

        switch (symbol) {
            case 'l':
                listNotes();
                break;
            case 'c':
                printf("Enter the title of the new note: ");
                scanf(" %[^\n]%*c", title);
                printf("Enter the contents of the note: ");
                scanf(" %[^\n]%*c", content);
                createNote(title, content);
                break;
            case 'v':
                printf("Enter the title of the note to view: ");
                scanf(" %[^\n]", title);
                viewNote(title);
                break;
            case 'e':
                printf("Enter the title of the note to edit: ");
                scanf(" %[^\n]%*c", title);
                editNote(title);
                break;
            case 'd':
                printf("Enter the title of the note to delete: ");
                scanf(" %[^\n]%*c", title);
                deleteNote(title);
                break;
            case 's':
                printf("Enter a keyword to search for: ");
                scanf(" %[^\n]", keyword);
                searchNotes(keyword);
                break;
            case 'n':
                printf("Enter the file name: ");
                scanf(" %[^\n]%*c", filename);
                importNotes(filename);
                break;
            case 'x':
                printf("Enter the file name: ");
                scanf(" %[^\n]%*c", filename);
                exportNotes(filename);
                break;
            case 'q':
                exitProgram(numNotesCreated, numNotesDeleted);
                break;
            default:
                printf("Invalid character.\n");
                break;
        }

        printf("\n");

    } while (symbol != 'q');
	return 0;
}