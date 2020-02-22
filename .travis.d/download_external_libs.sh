#!/usr/bin/env bash
set -e
curl -sL https://github.com/DolceSDK/ddpm/raw/master/ddpm -o ddpm
chmod +x ddpm
curl -L https://github.com/DolceSDK/ddpm/raw/master/include/install-packages.sh -o install-packages.sh
sed -i "s/\.\.\///" install-packages.sh
curl -L https://github.com/DolceSDK/ddpm/raw/master/install-all.sh | sed -e "s/include\///" | bash > /dev/null
rm ddpm
