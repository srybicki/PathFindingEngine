xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Plane {
    FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 1.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Plane mesh
      4;
      -1.000000;-1.000000; 2.000000;,
       1.000000;-1.000000; 2.000000;,
       1.000000; 1.000000; 2.000000;,
      -1.000000; 1.000000; 2.000000;;
      1;
      4;3,2,1,0;;
      MeshNormals { // Plane normals
        1;
         0.000000; 0.000000; 1.000000;;
        1;
        4;0,0,0,0;;
      } // End of Plane normals
      MeshTextureCoords { // Plane UV coordinates
        4;
         0.000100; 0.999900;,
         0.999900; 0.999900;,
         0.999900; 0.000100;,
         0.000100; 0.000100;;
      } // End of Plane UV coordinates
      MeshMaterialList { // Plane material list
        1;
        1;
        0;
        Material matNode {
           0.000000; 0.008466; 1.000000; 1.000000;;
           96.078431;
           0.000000; 0.000000; 0.000000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"BlueNode.png";}
        }
      } // End of Plane material list
    } // End of Plane mesh
  } // End of Plane
} // End of Root
