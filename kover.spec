Name: kover
Summary: WYSIWYG CD cover printer with CDDB support
Version: 2.9.5
Release: 1
License: GPL2
Group: Applications/Publishing
Source: http://lisas.de/kover/kover-%{version}.tar.gz
URL: http://lisas.de/kover/
Buildroot: %{_tmppath}/%{name}-%{version}-root

%description
Kover is an easy to use WYSIWYG CD cover printer with CDDB support. 

%prep
%setup -q
./configure --prefix=%{_prefix}

%build
make 

%clean
rm -rf $RPM_BUILD_ROOT

%install
%makeinstall

%files
%defattr(644,root,root,755)
%doc AUTHORS README COPYING TODO INSTALL THANKS ChangeLog  
%{_datadir}/apps/kover/koverui.rc
%{_datadir}/applnk/Multimedia/kover.desktop
%{_datadir}/icons/*/*/*/*
%{_datadir}/locale/*/*/*
%{_datadir}/apps/kover/pics/*
%{_datadir}/mimelnk/application/x-kover.desktop
%{_mandir}/man1/*
%attr(755,root,root)%{_bindir}/kover 
%attr(755,root,root)%{_bindir}/cddb-id

%changelog
* Mon Mar 10 2003 Adrian Reber <adrian@lisas.de>
 - Changed Copyright: to License:

* Sun Nov 18 2001 Adrian Reber <adrian@lisas.de>
 - Included mime type

* Fri Jun 22 2001 Adrian Reber <adrian@lisas.de>
 - Integrated spec file in autoconf

* Fri May 11 2001 Adrian Reber <adrian@lisas.de>
 - Updated to kover 0.6

* Fri May 11 2001 Adrian Reber <adrian@lisas.de>
 - Initial release of kover-0.5 rpm
