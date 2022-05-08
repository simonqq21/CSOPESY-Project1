/* Each job has a pid, burst time, and arrival time. Each job also has a
dynamically allocated array of timeframes. */
// Each timeframe has a start time and an end time.
// Sort the jobs based on arrival time in ascending order

typedef struct Timeframe {
  int start;
  int end;
  struct Timeframe * next;
} Timeframe_t;

typedef struct Process {
  int pid;
  int arrival;
  int burst;

} Process_t;
