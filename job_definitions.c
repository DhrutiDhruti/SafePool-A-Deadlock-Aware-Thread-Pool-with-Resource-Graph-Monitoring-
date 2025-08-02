#include <unistd.h>
#include "logger.h"
#include "rag.h"
#include "job_definitions.h"

void job_A(void* arg) {
log_event("Job A started");
rag_add_edge("JobA", "R1"); // request
sleep(1);
rag_add_edge("R1", "JobA"); // acquired

rag_add_edge("JobA", "R2"); // request second resource
sleep(1);
rag_add_edge("R2", "JobA"); // acquired

// Clean up
//rag_remove_edge("JobA", "R1");
//rag_remove_edge("R1", "JobA");
//rag_remove_edge("JobA", "R2");
//rag_remove_edge("R2", "JobA");
log_event("Job A finished");
}

void job_B(void* arg) {
log_event("Job B started");
rag_add_edge("JobB", "R2"); // request
sleep(1);
rag_add_edge("R2", "JobB"); // acquired
rag_add_edge("JobB", "R1"); // request second resource
sleep(1);
rag_add_edge("R1", "JobB"); // acquired

// Clean up
//rag_remove_edge("JobB", "R2");
//rag_remove_edge("R2", "JobB");
//rag_remove_edge("JobB", "R1");
//rag_remove_edge("R1", "JobB");
log_event("Job B finished");
}


