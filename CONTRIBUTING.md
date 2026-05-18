# Contributing

Thanks for contributing to the Kleine Graphen Bibliothek. This file describes how to work with the project and how tasks are split for a 3-person team.

Workflow
- Fork (if using GitHub) or clone the repository.
- Create a feature branch from `main` named `feature/<topic>-<yourname>`.
- Open a PR to `main` and request review from at least one teammate before merging.

Code style
- Use C++17. Keep headers under `include/graph` and sources under `src`.
- Add tests to `tests/` and examples to `examples/`.

Testing and CI
- Run locally:
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Assigning tasks
- See `README.md` for the team assignment table.
