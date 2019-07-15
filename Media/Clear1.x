xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame emptyLand {
    FrameTransformMatrix {
       4.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 4.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 2.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // emptyLand mesh
      4;
       1.000000; 1.000000; 0.000000;,
      -1.000000; 1.000000; 0.000000;,
      -1.000000;-1.000000; 0.000000;,
       1.000000;-1.000000; 0.000000;;
      1;
      4;3,2,1,0;;
      MeshNormals { // emptyLand normals
        1;
         0.000000;-0.000000; 1.000000;;
        1;
        4;0,0,0,0;;
      } // End of emptyLand normals
      MeshTextureCoords { // emptyLand UV coordinates
        4;
         0.020537; 0.213270;,
         0.212451; 0.213270;,
         0.212451; 0.021356;,
         0.020537; 0.021356;;
      } // End of emptyLand UV coordinates
      MeshMaterialList { // emptyLand material list
        1;
        1;
        0;
        Material matWhite {
           1.000000; 1.000000; 1.000000; 1.000000;;
           96.078431;
           0.000000; 0.000000; 0.000000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"Map.png";}
        }
      } // End of emptyLand material list
    } // End of emptyLand mesh
  } // End of emptyLand
} // End of Root
