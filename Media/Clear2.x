xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame normalLand {
    FrameTransformMatrix {
       4.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 4.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 2.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // normalLand mesh
      4;
       1.000000; 1.000000; 0.000000;,
      -1.000000; 1.000000; 0.000000;,
      -1.000000;-1.000000; 0.000000;,
       1.000000;-1.000000; 0.000000;;
      1;
      4;3,2,1,0;;
      MeshNormals { // normalLand normals
        1;
         0.000000;-0.000000; 1.000000;;
        1;
        4;0,0,0,0;;
      } // End of normalLand normals
      MeshTextureCoords { // normalLand UV coordinates
        4;
         0.234270; 0.643360;,
         0.426260; 0.643360;,
         0.426260; 0.450364;,
         0.234270; 0.450364;;
      } // End of normalLand UV coordinates
      MeshMaterialList { // normalLand material list
        1;
        1;
        0;
        Material matGrass {
           0.154817; 0.800000; 0.000000; 1.000000;;
           96.078431;
           0.000000; 0.000000; 0.000000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"Map.png";}
        }
      } // End of normalLand material list
    } // End of normalLand mesh
  } // End of normalLand
} // End of Root
