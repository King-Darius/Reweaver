We are excited that you want to contribute to Reweaver! There are many ways to help:

## Developing

Reweaver is primarily written in modern C++. Familiarity with QML and Qt will also help when working on the new UI layer.

If you want to develop Reweaver:

* Start by reading the build instructions in [BUILDING.md](BUILDING.md).
* Review our [engineering guidelines](https://github.com/Reweaver/Reweaver/wiki/Coding-standards) (coming soon). Until that wiki is published, follow the conventions you see in the existing code.
* All contributors must sign the [Contributor License Agreement](https://github.com/Reweaver/Reweaver/wiki/Contributor-License-Agreement) before we can merge code.
* Development discussions happen in [GitHub Discussions](https://github.com/Reweaver/Reweaver/discussions) and the community Matrix room linked in the README.

### Developing plug-ins

Reweaver supports a wide variety of plug-in APIs, including Nyquist, LV2, Audio Units (macOS only) and VST2 effects. Plug-ins are usually distributed separately from the main application, but they can still have a huge impact on the Reweaver community. Share your plug-ins in the Discussions board or the community chat so others can try them out.

## Testing & filing bugs

You can download development builds from the repository’s CI once they become available. Until then you can build the project locally. When reporting bugs:

* Include your operating system, compiler/toolchain and commit hash.
* Share clear reproduction steps so we can triage issues quickly.
* For regressions tied to an open pull request, comment directly on that PR. For everything else, open an issue using the [bug report template](https://github.com/Reweaver/Reweaver/issues/new/choose).

## Translating

We plan to reuse the translation infrastructure that powered previous releases. If you are interested in helping translate Reweaver, please watch the repository for announcements—we will publish localization instructions soon.

## Feedback & feature requests

We track feature ideas in [GitHub Discussions](https://github.com/Reweaver/Reweaver/discussions/categories/ideas) and in the issue tracker. Share your thoughts early so we can shape the roadmap together.

## Supporting users

Community support currently happens in [GitHub Discussions](https://github.com/Reweaver/Reweaver/discussions/categories/q-a) and the Matrix channel. If you create tutorials or walkthroughs, mention the Reweaver build you used so other users can follow along even as the project evolves rapidly.
