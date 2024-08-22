build_cmd = """
clang++ \
    -std=c++14 \
    -o Purrooser \
    src/Main.cpp \
    src/Purrooser/Purrooser.cpp \
    src/Utils/Actions/Actions.cpp \
    src/Utils/Utils.cpp \
    src/Window/PurrooserFrame.cpp \
    `wx-config --cxxflags --libs core base webview` > $(OUTS)
"""

purrooser_cmd = """
echo "Building..." > $(OUTS)
"""

genrule(
    name = "Build",
    outs = ["Purrooser.txt"],
    cmd = build_cmd,
)

genrule(
    name = "Purrooser",
    outs = ["BuildMain.txt"],
    cmd = purrooser_cmd,
    tools = ["//:Build"],
)
