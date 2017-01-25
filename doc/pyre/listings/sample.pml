<?xml version="1.0" encoding="utf-8"?>

<!--
  michael a.g. aïvázis <michael.aivazis@para-sim.com>
  (c) 2003-2017 all rights reserved
-->

<config>
  <!-- override the defaults in the component source code -->
  <component family="isce.topography.dem.srtm">
    <bind property="region"> [] </bind>
    <bind property="resolution"> 1 </bind>
  </component>

  <!-- for an instance named la -->
  <component name="la">
    <bind property="region">{regions.LA}</bind>
  </component>

  <!-- for an instance named greece -->
  <component name="greece">
    <bind property="resolution">3</bind>
    <bind property="region">{regions.Greece}</bind>
  </component>

  <!-- region aliases -->
  <bind property="regions.LA">(33.3,-118.4), (35.7,-116.8)</bind>
  <bind property="regions.Greece">(41,26), (39,19), (34,24), (36,29)</bind>

</config>

<!-- end of file -->
