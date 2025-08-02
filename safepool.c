#include <stdio.h>
#include <unistd.h>
#include "thpool.h"
#include "job_definitions.h"
#include "logger.h"
#include "rag.h"

int main() {
init_logger("log.txt");
threadpool pool = thpool_init(2); // Only 2 threads

thpool_add_work(pool, job_A, NULL);
thpool_add_work(pool, job_B, NULL);

sleep(8);

thpool_wait(pool);

rag_export_dot("rag.dot"); // Generate RAG DOT file
if (rag_has_cycle()) {
    log_event("❌ Deadlock detected!");
    printf("❌ Deadlock detected!\n");
} else {
    log_event("✅ No deadlock detected.");
    printf("✅ No deadlock detected.\n");
}

close_logger();
thpool_destroy(pool);
return 0;
}
