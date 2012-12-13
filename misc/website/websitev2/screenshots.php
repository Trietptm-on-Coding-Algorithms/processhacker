<?php $pagetitle = "Screenshots"; include "header.php"; ?>

<div id="page">
    <div class="yui-d0">
        <nav>
            <img class="flowed-block" src="images/logo_64x64.png" alt="Project Logo" width="64" height="64">

            <div class="flowed-block">
                <h2>Process Hacker</h2>
                <ul class="facetmenu">
                    <li><a href="/">Overview</a></li>
                    <li><a href="features.php">Features</a></li>
                    <li class="active"><a href="screenshots.php">Screenshots</a></li>
                    <li><a href="downloads.php">Downloads</a></li>
                    <li><a href="faq.php">FAQ</a></li>
                    <li><a href="about.php">About</a></li>
                    <li><a href="forums/">Forum</a></li>
                </ul>
            </div>
        </nav>
    </div>

    <div class="yui-g">
        <div class="yui-u first">
            <a class="fancybox" data-fancybox-group="gallery" href="images/screenshots/processes_tab_large.png" title="Main window">
                <img src="images/screenshots/processhacker_small.png" alt="Main window thumb" width="200" height="107"/>
            </a>

            <a class="fancybox" data-fancybox-group="gallery" href="images/screenshots/servicestab_large.png" title="Services tab">
                <img src="images/screenshots/servicestab_small.png" alt="Services tab thumb" width="200" height="107"/>
            </a>

            <a class="fancybox" data-fancybox-group="gallery" href="images/screenshots/networktab_large.png" title="Network tab">
                <img src="images/screenshots/networktab_small.png" alt="Network tab thumb" width="200" height="107"/>
            </a>

            <a class="fancybox" data-fancybox-group="gallery" href="images/screenshots/sysinfo_large.png" title="Sysinfo window">
                <img src="images/screenshots/sysinfo_small.png" alt="Sysinfo window thumb" width="200" height="107"/>
            </a>
        </div>
    </div>
</div>

<?php $includejs = true; include "footer.php"; ?>
