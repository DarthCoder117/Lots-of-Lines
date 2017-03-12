namespace LotsOfLinesExcel
{
    partial class LotsOfLinesRibbon : Microsoft.Office.Tools.Ribbon.RibbonBase
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        public LotsOfLinesRibbon()
            : base(Globals.Factory.GetRibbonFactory())
        {
            InitializeComponent();
        }

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lotsOfLinesTab = this.Factory.CreateRibbonTab();
            this.lotsOfLinesGroup = this.Factory.CreateRibbonGroup();
            this.parallelCoordinatesButton = this.Factory.CreateRibbonButton();
            this.collocatedCoordinatesButton = this.Factory.CreateRibbonButton();
            this.radialCoordinatesButton = this.Factory.CreateRibbonButton();
            this.shiftedCoordinatesButton = this.Factory.CreateRibbonButton();
            this.group1 = this.Factory.CreateRibbonGroup();
            this.settingsButton = this.Factory.CreateRibbonButton();
            this.lotsOfLinesTab.SuspendLayout();
            this.lotsOfLinesGroup.SuspendLayout();
            this.group1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lotsOfLinesTab
            // 
            this.lotsOfLinesTab.Groups.Add(this.lotsOfLinesGroup);
            this.lotsOfLinesTab.Groups.Add(this.group1);
            this.lotsOfLinesTab.Label = "Lots Of Lines";
            this.lotsOfLinesTab.Name = "lotsOfLinesTab";
            // 
            // lotsOfLinesGroup
            // 
            this.lotsOfLinesGroup.Items.Add(this.parallelCoordinatesButton);
            this.lotsOfLinesGroup.Items.Add(this.collocatedCoordinatesButton);
            this.lotsOfLinesGroup.Items.Add(this.radialCoordinatesButton);
            this.lotsOfLinesGroup.Items.Add(this.shiftedCoordinatesButton);
            this.lotsOfLinesGroup.Label = "Visualizations";
            this.lotsOfLinesGroup.Name = "lotsOfLinesGroup";
            // 
            // parallelCoordinatesButton
            // 
            this.parallelCoordinatesButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.parallelCoordinatesButton.Image = global::LotsOfLinesExcel.Properties.Resources.parallel;
            this.parallelCoordinatesButton.Label = "Parallel Coordinates";
            this.parallelCoordinatesButton.Name = "parallelCoordinatesButton";
            this.parallelCoordinatesButton.ShowImage = true;
            // 
            // collocatedCoordinatesButton
            // 
            this.collocatedCoordinatesButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.collocatedCoordinatesButton.Image = global::LotsOfLinesExcel.Properties.Resources.Collocated;
            this.collocatedCoordinatesButton.Label = "Colocated Paired Coordinates";
            this.collocatedCoordinatesButton.Name = "collocatedCoordinatesButton";
            this.collocatedCoordinatesButton.ShowImage = true;
            this.collocatedCoordinatesButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.button1_Click);
            // 
            // radialCoordinatesButton
            // 
            this.radialCoordinatesButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.radialCoordinatesButton.Image = global::LotsOfLinesExcel.Properties.Resources.Anchored;
            this.radialCoordinatesButton.Label = "Radial Paired Coordinates";
            this.radialCoordinatesButton.Name = "radialCoordinatesButton";
            this.radialCoordinatesButton.ShowImage = true;
            // 
            // shiftedCoordinatesButton
            // 
            this.shiftedCoordinatesButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.shiftedCoordinatesButton.Image = global::LotsOfLinesExcel.Properties.Resources.Shifted;
            this.shiftedCoordinatesButton.Label = "Shifted Paired Coordinates";
            this.shiftedCoordinatesButton.Name = "shiftedCoordinatesButton";
            this.shiftedCoordinatesButton.ShowImage = true;
            // 
            // group1
            // 
            this.group1.Items.Add(this.settingsButton);
            this.group1.Label = "Other";
            this.group1.Name = "group1";
            // 
            // settingsButton
            // 
            this.settingsButton.Label = "Settings";
            this.settingsButton.Name = "settingsButton";
            this.settingsButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.settingsButton_Click);
            // 
            // LotsOfLinesRibbon
            // 
            this.Name = "LotsOfLinesRibbon";
            this.RibbonType = "Microsoft.Excel.Workbook";
            this.Tabs.Add(this.lotsOfLinesTab);
            this.Load += new Microsoft.Office.Tools.Ribbon.RibbonUIEventHandler(this.LotsOfLinesRibbon_Load);
            this.lotsOfLinesTab.ResumeLayout(false);
            this.lotsOfLinesTab.PerformLayout();
            this.lotsOfLinesGroup.ResumeLayout(false);
            this.lotsOfLinesGroup.PerformLayout();
            this.group1.ResumeLayout(false);
            this.group1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        internal Microsoft.Office.Tools.Ribbon.RibbonTab lotsOfLinesTab;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup lotsOfLinesGroup;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton parallelCoordinatesButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup group1;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton collocatedCoordinatesButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton radialCoordinatesButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton shiftedCoordinatesButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton settingsButton;
    }

    partial class ThisRibbonCollection
    {
        internal LotsOfLinesRibbon LotsOfLinesRibbon
        {
            get { return this.GetRibbon<LotsOfLinesRibbon>(); }
        }
    }
}
