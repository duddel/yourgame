# Development

## Notes

-   A new [release](https://github.com/duddel/yourgame/releases) every couple of weeks, if something meaningful happens
-   Semantic Versioning approach (`MAJOR.MINOR.PATCH`)
    -   **But none of the rules regarding compatibility apply as long as `MAJOR` version is 0**
    -   Expect breaking API changes, catch up using the [Changelog](Changelog.md)
-   `yourgame` is based on `yourgamelib`, which is hosted [here](https://github.com/duddel/yourgamelib)
-   `ToDo`s are scattered in the code and docs. No dedicated list.

## Release Checklist

### Before Tag

-   Check if version is correct in `project()` in `CMakeLists.txt`
-   Check if version is correct in [Changelog](Changelog.md)
-   Remove `(unreleased)` from version in [Changelog](Changelog.md)
-   Check generated build artifacts (`Actions`)
-   Check web demo

### After Tag

-   Create release on GitHub and upload build artifacts
-   Set next version in `project()` in `CMakeLists.txt`
-   Add next version to [Changelog](Changelog.md) with `(unreleased)`
