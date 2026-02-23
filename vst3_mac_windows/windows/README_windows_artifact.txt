Windows VST3 artifact was not downloadable from this environment because
GitHub Actions artifact download requires authenticated API access.

To place the Windows VST3 here, use one of these options:

1) GitHub Web UI (recommended)
- Open repository Actions
- Open the latest successful Windows run (CI or Release)
- Download artifact with Windows VST3 zip
- Extract/copy the .vst3 into this folder:
  /Users/grzzi/Desktop/dnb_bass_synth/vst3_mac_windows/windows

2) CLI with token
- Set a GitHub PAT with repo/actions read access:
  export GITHUB_TOKEN=...
- Then download artifact zip via API and extract it here.
