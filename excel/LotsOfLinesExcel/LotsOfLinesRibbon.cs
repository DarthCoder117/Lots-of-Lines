using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Office.Tools.Ribbon;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace LotsOfLinesExcel
{
    public partial class LotsOfLinesRibbon
    {
        private void LotsOfLinesRibbon_Load(object sender, RibbonUIEventArgs e)
        {
            parallelCoordinatesButton.Click += ParallelCoordinatesButton_Click;
            collocatedCoordinatesButton.Click += CollocatedCoordinatesButton_Click;
            radialCoordinatesButton.Click += RadialCoordinatesButton_Click;
            shiftedCoordinatesButton.Click += ShiftedCoordinatesButton_Click;
        }

        private Dictionary<int, string> tempFileMap = new Dictionary<int, string>();

        private void ParallelCoordinatesButton_Click(object sender, RibbonControlEventArgs e)
        {
            OpenApplication(true, false, false, false);
        }

        private void CollocatedCoordinatesButton_Click(object sender, RibbonControlEventArgs e)
        {
            OpenApplication(false, true, false, false);
        }

        private void RadialCoordinatesButton_Click(object sender, RibbonControlEventArgs e)
        {
            OpenApplication(false, false, true, false);
        }

        private void ShiftedCoordinatesButton_Click(object sender, RibbonControlEventArgs e)
        {
            OpenApplication(false, false, false, true);
        }

        /// <summary>
        /// Launch the Lots of Lines application with the selected visualization methods.
        /// </summary>
        private void OpenApplication(bool parallel, bool collocated, bool radial, bool shifted)
        {
            //Create temp CSV file
            string tempPath = System.IO.Path.GetTempPath();
            string tempFile = tempPath + Guid.NewGuid().ToString() + ".csv";
            FileStream stream = File.Create(tempFile);
            stream.Close();

            Globals.ThisAddIn.Application.ActiveWorkbook.SaveAs(tempFile, Excel.XlFileFormat.xlCSV, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Excel.XlSaveAsAccessMode.xlNoChange);

            //Open Lots of Lines application
            string lotsOfLinesDir = Properties.Settings.Default.LotsOfLinesPath;
            string lotsOfLinesFilename = lotsOfLinesDir + "\\LotsOfLinesApp.exe";
            try
            {
                string args = tempFile;
                if (parallel) args += " -p";
                if (collocated) args += " -c";
                if (radial) args += " -r";
                if (shifted) args += " -s";

                Process proc = Process.Start(lotsOfLinesFilename, args);

                tempFileMap[proc.Id] = tempFile;
                proc.Exited += Proc_Exited;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error loading Lots of Lines. Please check that your path is set.");
            }

            Excel.Workbook workbook = Globals.ThisAddIn.Application.ActiveWorkbook;
        }

        private void Proc_Exited(object sender, EventArgs e)
        {
            Process proc = (Process)sender;

            string tempFile = tempFileMap[proc.Id];
            try
            {
                File.Delete(tempFile);
            }
            catch (Exception ex)
            {
                Console.Out.WriteLine(ex.Message);
            }
        }

        private void editBox1_TextChanged(object sender, RibbonControlEventArgs e)
        {

        }

        private void button1_Click(object sender, RibbonControlEventArgs e)
        {

        }

        private void settingsButton_Click(object sender, RibbonControlEventArgs e)
        {
            SettingsDialog dlg = new SettingsDialog();
            dlg.ShowDialog();
        }
    }
}
