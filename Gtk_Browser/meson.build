project('Browser', 'cpp', default_options : ['cpp_std=c++23'])

gtk_dep = dependency('gtk4')
webkit_dep = dependency('webkitgtk-6.0')

executable('Browser',
    ['browser.cpp', 'main.cpp'],
    dependencies: [gtk_dep, webkit_dep]
)
