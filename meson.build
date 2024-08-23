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
    'src/Main.cc',
    'src/Main.hh',
    'src/Purrooser/Purrooser.cc',
    'src/Purrooser/Purrooser.hh',
    'src/Utils/Actions/Actions.cc',
    'src/Utils/Actions/Actions.hh',
    'src/Utils/Utils.cc',
    'src/Utils/Utils.hh',
    'src/Window/PurrooserFrame.cc',
    'src/Window/PurrooserFrame.hh',
    dependencies : [wxwidgets_dep],
)
