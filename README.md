# Reweaver

Reweaver is an open-source, multi-track audio editor and recorder built for creators who need fast, reliable and modern tooling across Windows, macOS and Linux. The project is a continuation of the work started in the Audacity 4 redesign, re-imagined with a new name, refreshed goals, and a strong focus on collaboration and extensibility.

## Project status

Reweaver is under active development. The codebase is currently going through large architectural changes as we iterate on the new user experience and modernize the engine. Expect breaking changes and rapid iteration while we stabilize the first public releases.

You can keep track of major milestones and announcements through the following channels:

* [Project roadmap](https://github.com/Reweaver/Reweaver/discussions/categories/announcements)
* [Developer updates](https://github.com/Reweaver/Reweaver/discussions)
* [Community chat](https://matrix.to/#/#reweaver:matrix.org)

## Getting started

Reweaver shares many of its foundations with MuseScore Studio. Until we finish moving all content into this repository, the high-level setup process mirrors the MuseScore developer guide:

1. [Set up a developer environment](https://github.com/musescore/MuseScore/wiki/Set-up-developer-environment)
2. [Install Qt and Qt Creator](https://github.com/musescore/MuseScore/wiki/Install-Qt-and-Qt-Creator)

### Build instructions

Full build steps live in [BUILDING.md](BUILDING.md). At a glance the flow is:

```bash
cmake -S . -B build -G Ninja # configure (first build only)
cmake --build build          # compile
cmake --install build        # install artifacts
```

We also ship helper scripts for Visual Studio and CI in the repository root.

### Nightly builds

Automated builds will become available later in the development cycle. In the meantime you can create your own binaries by following the build instructions above.

## Contributing

We welcome bug reports, feature ideas, documentation help and code contributions. Please read [CONTRIBUTING.md](CONTRIBUTING.md) for detailed guidelines covering development workflows, testing expectations and community standards.

If you would like to chat with the team, join the developer discussions in GitHub or visit the Matrix channel linked above.

## License

Reweaver is released under the GPLv3 license. Most source files are GPLv2-or-later unless otherwise noted (for example, third-party libraries in `/lib-src`). Documentation is licensed under CC BY 3.0 unless we explicitly mark otherwise. Full details are available in [LICENSE.txt](LICENSE.txt).
