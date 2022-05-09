/* Each job has a pid, burst time, and arrival time. Each job also has a
dynamically allocated array of timeframes. */
// Each timeframe has a start time and an end time.
// Sort the jobs based on arrival time in ascending order

typedef struct {
  int start;
  int end;
  struct Timeframe * next;
} Timeframe_t;

typedef struct {
  int pid;
  int arrival;
  int burst;
  Timeframe_t * timeframes;
  struct Process_t *next;
} Process_t;


typedef struct {
  Process_t *head;
  Process_t *tail;
} ProcessQueue;

ProcessQueue* createProcessQueue(void);
