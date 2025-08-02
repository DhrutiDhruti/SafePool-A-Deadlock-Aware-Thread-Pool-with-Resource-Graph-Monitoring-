# SafePool – A Deadlock-Aware Thread Pool with Resource Graph Monitoring

SafePool is a modular thread pool system built using POSIX threads that simulates real-world job-resource allocation scenarios and detects potential deadlocks using a Resource Allocation Graph (RAG). It provides a visual representation of how jobs interact with resources and highlights cycles that indicate deadlock conditions.

This project is designed as a learning tool to explore key concepts in operating systems such as deadlocks, synchronization, and concurrent job execution.

## Key Features

- Thread pool implemented using POSIX pthread API
- Dynamic Resource Allocation Graph (RAG) built at runtime
- Deadlock detection using cycle detection in the RAG
- Generates a DOT-format graph (rag.dot) for visualization
- Logs job activity and system events in log.txt
- Modular architecture separating thread pool, job logic, logging, and graph logic

## Project Structure

```
SafePool/
├── safepool.c           # Main program to run the thread pool
├── thpool.c/h           # Thread pool implementation
├── rag.c/h              # RAG logic and deadlock detection
├── job_definitions.c/h  # Simulated job behaviors and resource usage
├── logger.c/h           # Logging utility to log.txt
├── rag.dot              # DOT-format graph file output
├── Makefile             # Compilation script
```

## How to Compile and Run

Make sure you are running on a Unix-based environment (Linux/macOS) and have GCC and Make installed.

1. Open terminal and clone/download the repository.

2. Build the project:

   ```bash
   make clean && make
   ```

3. Run the executable:

   ```bash
   ./safepool
   ```

4. View the output:

   - The console will show whether a deadlock was detected or not.
   - rag.dot will contain the resource allocation graph.

To visualize the graph (optional):

```bash
dot -Tpng rag.dot -o rag.png
```

This requires Graphviz to be installed.

## Example Output

Console:
```
Job A started
Job B started
❌ Deadlock detected!
```

Graph (rag.dot):
```
"JobA" -> "R1";
"R1" -> "JobA";
"JobB" -> "R2";
"R2" -> "JobB";
"JobA" -> "R2";
"JobB" -> "R1";
```

This graph indicates a cycle between JobA and JobB through R1 and R2, signaling a deadlock.

## Concepts Demonstrated

- Thread pool creation and management
- Deadlock detection via cycle finding
- Resource modeling using graphs
- Logging and system monitoring
- Modular C programming with headers and implementations

## Author

Dhruti Dobariya,
M.E. Computer Science  
BITS Pilani, Hyderabad Campus
