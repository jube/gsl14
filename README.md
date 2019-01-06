# Guidelines Support Library (for C++14)


## Comparison with other GSL implementations

- [Microsoft GSL](https://github.com/Microsoft/GSL) (`microsoft`)
- [mattia.basaglia/Melanolib](https://gitlab.com/mattia.basaglia/Melanolib/blob/master/include/melanolib/utils/gsl.hpp) (`basaglia`)
- this library (`jube`)

### GSL specifications

| Feature           | `microsoft` | `basaglia` | `jube` |
|-------------------|:-----------:|:----------:|:------:|
| `owner`           |      ✓      |      ✓     |    ✓   |
| `not_null`        |      ✓      |      ✓     |    ✓   |
| `span`            |      ✓      |      ✓     |    ✓   |
| `span_p`          |      ✓      |      ✓     |    ✓   |
| `string_span`     |      ✓      |      ✓     |    ✓   |
| `cstring_span`    |      ✓      |      ✓     |    ✓   |
| `zstring`         |      ✓      |      ✓     |    ✓   |
| `czstring`        |      ✓      |      ✓     |    ✓   |
| `unique_ptr`      |      ✓      |      ✓     |    ✓   |
| `shared_ptr`      |      ✓      |      ✓     |    ✓   |
| `stack_array`     |             |      ✓     |    ✓   |
| `dyn_array`       |             |      ✓     |    ✓   |
| `Expects`         |      ✓      |      ✓     |    ✓   |
| `Ensures`         |      ✓      |      ✓     |    ✓   |
| `final_action`    |      ✓      |      ✓     |    ✓   |
| `finally`         |      ✓      |      ✓     |    ✓   |
| `narrow_cast`     |      ✓      |      ✓     |    ✓   |
| `narrow`          |      ✓      |      ✓     |    ✓   |
| `move_owner`      |      ✓      |      ✓     |    ✓   |
| `joining_thread`  |      ✓      |      ✓     |    ✓   |
| `index`           |      ✓      |      ✓     |    ✓   |

### GSL extensions or past specifications

| Feature           | `microsoft` | `basaglia` | `jube` |
|-------------------|:-----------:|:----------:|:------:|
| `copy`            |      ✓      |            |        |
| `byte`            |      ✓      |            |        |
| `at`              |      ✓      |            |        |
| `multi_span`      |      ✓      |            |        |
| `*string_span`    |      ✓      |            |        |
| ``           |      ✓      |    ✓    |      ✓     |    ✓   |
| ``           |      ✓      |    ✓    |      ✓     |    ✓   |
| ``           |      ✓      |    ✓    |      ✓     |    ✓   |
