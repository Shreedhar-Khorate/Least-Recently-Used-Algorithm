#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;

    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }

    return pos;
}

void printTable(int frames[], int no_of_frames) {
    for (int j = 0; j < no_of_frames; ++j) {
        if (frames[j] != -1)
            printf("%d ", frames[j]);
        else
            printf("- ");
    }
    printf("\n");
}

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;

    printf("Enter the number of frames: ");
    scanf("%d", &no_of_frames);

    printf("Enter the number of pages: ");
    scanf("%d", &no_of_pages);

    printf("Enter the reference string: ");
    for (i = 0; i < no_of_pages; ++i) {
        scanf("%d", &pages[i]);
    }

    // Initialize the frames to -1 (empty)
    for (i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
    }

    printf("\n---------------------------------\n");
    printf("| Page Reference | Frame State  |\n");
    printf("---------------------------------\n");

    for (i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;

        // Check if page is already in frame
        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            // Check if there is an empty frame
            for (j = 0; j < no_of_frames; ++j) {
                if (frames[j] == -1) {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            // Replace the least recently used page
            pos = findLRU(time, no_of_frames);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        // Print the current state of frames in the table format
        printf("|       %d        |  ", pages[i]);
        printTable(frames, no_of_frames);
    }

    printf("---------------------------------\n");

    // Calculate page hits
    int page_hit = no_of_pages - faults;

    // Display total page faults and hits
    printf("\nTotal Page Faults = %d", faults);
    printf("\nTotal Page Hits = %d", page_hit);

    // Calculate and display hit ratio
    float hit_ratio = (float)page_hit / no_of_pages;  // Ensure floating-point division
    printf("\nHit Ratio = %.2f\n", hit_ratio);

    return 0;
}