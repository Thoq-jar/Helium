project('Purrooser', 'cpp', default_options : ['cpp_std=c++14'])

wxwidgets_dep = dependency(
    'wxwidgets', modules : [
        'core',
        'base',
        'webview'
    ],
)

executable(
    'Purrooser',
    'src/Main.cpp',
    'src/Main.hpp',
    'src/Purrooser/Purrooser.cpp',
    'src/Purrooser/Purrooser.hpp',
    'src/Utils/Actions/Actions.cpp',
    'src/Utils/Actions/Actions.hpp',
    'src/Utils/Utils.cpp',
    'src/Utils/Utils.hpp',
    'src/Window/PurrooserFrame.cpp',
    'src/Window/PurrooserFrame.hpp',
    dependencies : [wxwidgets_dep],
)